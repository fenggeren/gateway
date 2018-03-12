//
// Created by HuanaoGroup on 2018/3/6.
//

#include "client_session.h"
#include "../net_work/net_receiver_buffer.h"
#include "net_send_buffer.h"
#include "../common/log.h"
#include "client_data_processor.h"


client_session::client_session(tcp::socket socket, std::shared_ptr<client_acceptor> accptor)
        : socket_(std::move(socket)),
          client_acceptor_(accptor)
{

}

client_session::~client_session()
{
    close();
}

std::string client_session::get_remote_ipaddress() const
{
    std::string ip_addr;

    if (socket_.is_open())
    {
        boost::system::error_code ec;
        auto client_endpoint = socket_.remote_endpoint(ec);
        if (!ec)
        {
            ip_addr = client_endpoint.address().to_string(ec);
        }
    }
    else
    {

    }
    return ip_addr;
}

tcp::socket& client_session::get_socket()
{
    return socket_;
}

void client_session::start_async_read()
{
    get_receiver_buffer()->start_async_read();
}

void client_session::handle_message(const std::string& msg)
{
    log_info(msg);
    auto accptor = client_acceptor_.lock();
    accptor->accept_data(shared_from_this());

    get_send_buffer()->send_data((byte *)msg.data(), msg.length());
}

std::shared_ptr<net_receiver_buffer> client_session::get_receiver_buffer()
{
    if (!receiver_buffer_)
    {
        receiver_buffer_ = std::make_shared<net_receiver_buffer>(shared_from_this());
    }
    return receiver_buffer_;
}

std::shared_ptr<net_send_buffer> client_session::get_send_buffer()
{
    if (!send_buffer_)
    {
        send_buffer_ = std::make_shared<net_send_buffer>(shared_from_this());
    }
    return send_buffer_;
}

void client_session::close()
{
    if (socket_.is_open())
    {
        boost::system::error_code ec;
        socket_.close(ec);
        log_info("socket closed");
    }
}

void client_session::receive_packet(word main_id, word sub_id, std::shared_ptr<net_packet> packet)
{

}

void client_session::send_packet(word main_id, word sub_id, std::shared_ptr<net_packet> packet)
{
    
}












