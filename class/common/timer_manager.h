//
// Created by HuanaoGroup on 2018/3/8.
//

#ifndef GATEWAY_TIMER_MANAGER_H
#define GATEWAY_TIMER_MANAGER_H

#include <memory>
#include <boost/asio.hpp>
#include <list>
#include "log.h"

class timer_manager;

class timer : boost::noncopyable
{
public:

    static std::shared_ptr<timer>
    scheduled_timer(boost::asio::io_service& io_service,
                           double interval,
                           const std::function<void()>& func,
                           bool repeats = false)
    {
        log_info("timer::scheduled_timer");
        auto tm = std::make_shared<timer>(io_service);
        tm->func_ = func;
        tm->repeats_ = repeats;
        tm->interval_ = interval;
        tm->scheduled_timer();
        return tm;
    }


    void cancel()
    {
        timer_.cancel();
    }

    timer(boost::asio::io_service& io_service)
            :timer_(io_service)
    {

    }
private:
    friend class timer_manager;



    void scheduled_timer();

private:
    boost::asio::deadline_timer timer_;
    bool  repeats_;
    double interval_;
    std::function<void()> func_;
};


class timer_manager
{
public:
    timer_manager(boost::asio::io_service& io_service)
            :io_service_(io_service)
    {

    }

    std::shared_ptr<timer>
    scheduled_timer(const std::function<void()>& func, double interval, bool repeats = false);

    void cancel(std::shared_ptr<timer> tm);

private:
    boost::asio::io_service& io_service_;
    std::list<std::shared_ptr<timer>> timers_;
};

#endif //GATEWAY_TIMER_MANAGER_H
