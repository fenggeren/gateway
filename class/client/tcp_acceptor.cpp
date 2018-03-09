//
// Created by HuanaoGroup on 2018/3/6.
//

#include "tcp_acceptor.h"
#include "client_session.h"
#include "client_data_processor.h"
#include "../common/log.h"

void tcp_acceptor::start(std::shared_ptr<client_acceptor> accptor)
{
    do_accept(accptor);
}

void tcp_acceptor::do_accept(std::shared_ptr<client_acceptor> accptor)
{
    acceptor_.async_accept(socket_,
            [this, accptor](const std::error_code& ec)
            {
                if (!ec)
                {
                    socket_.set_option(tcp::no_delay(true));
                    socket_.set_option(boost::asio::socket_base::keep_alive(true));
                    auto session = std::make_shared<client_session>(std::move(socket_), accptor);
                    accptor->accept_session(session);
                    do_accept(accptor);
                    log_info("client new session");
                }
                else
                {
                    socket_.shutdown(tcp::socket::shutdown_both);
                    log_err("client new session");
                }
            });
}