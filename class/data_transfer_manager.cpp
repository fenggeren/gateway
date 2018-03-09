//
// Created by HuanaoGroup on 2018/3/7.
//

#include "data_transfer_manager.h"
#include "client/tcp_acceptor.h"
#include "client/client_data_processor.h"
#include "client/client_session_manager.h"

#define net_port 7289

data_transfer_manager::data_transfer_manager(boost::asio::io_service &io_service)
{
    acceptor_ = std::make_shared<tcp_acceptor>(io_service, net_port);
//    session_manager_ = std::make_shared<client_session_manager>();
    client_processor_ = std::make_shared<client_data_processor>();
}


void data_transfer_manager::start()
{
    acceptor_->start(client_processor_);
}

