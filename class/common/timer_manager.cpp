//
// Created by HuanaoGroup on 2018/3/8.
//

#include "timer_manager.h"
#include "log.h"


void timer::scheduled_timer()
{
    timer_.expires_from_now(boost::posix_time::seconds(interval_));
    timer_.async_wait([this](const boost::system::error_code& ec)
                      {
                          if (!ec)
                          {
                              if (func_)
                              {
                                  func_();
                              }
                              if (repeats_)
                              {
                                  scheduled_timer();
                              }
                          }
                      });
}

std::shared_ptr<timer>
timer_manager::scheduled_timer(const std::function<void()>& func, double interval, bool repeats)
{
    log_info("scheduled_timer begin");
    auto timer = timer::scheduled_timer(io_service_, interval, func, repeats);
    timers_.push_back(timer);
    log_info("scheduled_timer end");
    return timer;
}



void timer_manager::cancel(std::shared_ptr<timer> tm)
{
    timers_.remove(tm);
    tm->cancel();
}