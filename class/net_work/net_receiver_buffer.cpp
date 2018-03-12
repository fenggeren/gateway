//
// Created by HuanaoGroup on 2018/3/7.
//

#include "net_receiver_buffer.h"
#include "../client/client_session.h"
#include <boost/bind.hpp>
#include "net_packet_config.h"
#include "net_packet.h"
#include "log.h"
#include "receive_packet_processor.h"

net_receiver_buffer::net_receiver_buffer(std::shared_ptr<client_session> session)
        : session_(session),
        recvd_size_(0)
{
    recv_buf_ = new byte[SOCKET_TCP_BUFFER];
    memset(recv_buf_, 0, SOCKET_TCP_BUFFER);
    packet_processor_ = std::make_shared<receive_packet_processor>(recv_buf_, recvd_size_);
}

net_receiver_buffer::~net_receiver_buffer()
{
    if (recv_buf_)
    {
        delete[] recv_buf_;
    }
    recv_buf_ = nullptr;
}


void net_receiver_buffer::start_async_read()
{
    auto session = session_.lock();
    if (session)
    {
        session->get_socket().async_read_some(
                boost::asio::buffer(recv_buf_ + recvd_size_, SOCKET_TCP_BUFFER - recvd_size_),
                boost::bind(&net_receiver_buffer::handle_read, this,
                            boost::asio::placeholders::error,
                            boost::asio::placeholders::bytes_transferred));
    }
}

void net_receiver_buffer::handle_read(const boost::system::error_code& ec,
                                      size_t bytes_transferred)
{
    auto session = session_.lock();
    if (!session)
    {
        return;
    }

    if (ec != boost::asio::error::operation_aborted)
    {
        try
        {
            if (!ec)
            {
                recvd_size_ += bytes_transferred;
//                scan_packets();
                packet_processor_->processor_packet(session);
                start_async_read();
            }
        }
        catch (const std::exception& e)
        {

        }
    }
}


void net_receiver_buffer::scan_packets()
{
    word packet_size = 0;
    tcp_head* head = (tcp_head*)recv_buf_;
    auto session = session_.lock();
    if (!session) return;

    while(recvd_size_ >= sizeof(tcp_head))
    {
        packet_size = head->info.packet_size;
        assert(packet_size <= (SOCKET_TCP_BUFFER));

        if (packet_size > recvd_size_) {
            session->close();
        }

        try
        {
            // 处理数据
            auto packet = create_packet(&recv_buf_[sizeof(tcp_head)],
                                             packet_size - sizeof(tcp_head));
            if (packet)
            {
                recvd_size_ -= packet_size;
                if (recvd_size_)
                {
                    memmove(recv_buf_, recv_buf_ + packet_size, recvd_size_);
                }
                session->receive_packet(head->command.main_cmd_id, head->command.sub_cmd_id, packet);
            }
            else
            {
                recvd_size_ -= packet_size;
                session->close();
            }

        }
        catch (const std::exception& e)
        {
            recvd_size_ = 0;
            session->close();
        }

    }
}


void net_receiver_buffer::handle_message(const std::string &msg)
{
    auto session = session_.lock();
    if (session)
    {
        session->handle_message(msg);
    }
}

