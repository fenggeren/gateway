//
// Created by HuanaoGroup on 2018/3/7.
//
#include <vector>
#include <list>

#include "client_session_manager.h"
#include "client_session.h"
#include "../net_config.h"
#include "log.h"
#include "timer_manager.h"

#define SLOT_COUNT 20

extern timer_manager *g_timer_manager;

class circle_sessions
{
public:
    circle_sessions()
    : sessions_(SLOT_COUNT)
    {

    }

    std::list<std::shared_ptr<client_session>>&
    get_current_slot()
    {
        return sessions_[cur_index_];
    }

    void add(std::shared_ptr<client_session> value)
    {
        get_current_slot().push_back(value);
    }

    void start()
    {
        schedule();
    }

    void stop()
    {
        g_timer_manager->cancel(timer_);
        timer_ = nullptr;
    }

private:

    void schedule()
    {
        log_info("=====schedule begin");
        timer_ = g_timer_manager->scheduled_timer([this]()
                                         {
                                             log_info("session circle timer schedule");
                                             clear_last_slot();

                                             cur_index_ += 1;
                                             cur_index_ %= SLOT_COUNT;
                                         }, 1, true);
    }

    void clear_last_slot()
    {
        int last_index = (cur_index_ + 1) % SLOT_COUNT;
        sessions_[last_index].clear();
    }

private:
    int cur_index_;
    std::shared_ptr<timer> timer_;
    std::vector<std::list<std::shared_ptr<client_session>>> sessions_;
};


//////////////////////////////////////////////////////////////////////

client_session_manager::client_session_manager()
{
    auto& io_service = global::get_io_service();
    circle_sessions_ = std::make_shared<circle_sessions>();
    circle_sessions_->start();
}

void client_session_manager::add_session(std::shared_ptr<client_session> session)
{
    circle_sessions_->add(session);
}

void client_session_manager::update_session(std::shared_ptr<client_session> session)
{
    circle_sessions_->add(session);
}

