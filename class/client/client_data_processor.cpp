//
// Created by HuanaoGroup on 2018/3/7.
//

#include "client_data_processor.h"
#include "client_session_manager.h"
#include "client_session.h"
#include "../common/log.h"

client_data_processor::client_data_processor()
{
    session_manager_ = std::make_shared<client_session_manager>();
}


void client_data_processor::accept_session(std::shared_ptr<client_session> session)
{
    // 处理 session
    log_info(session->get_remote_ipaddress());
    session->start_async_read();
    session_manager_->add_session(session);
}

void client_data_processor::accept_data(std::shared_ptr<client_session> session)
{
    session_manager_->update_session(session);
}
