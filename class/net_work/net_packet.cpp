//
// Created by HuanaoGroup on 2018/3/9.
//

#include "net_packet.h"
#include <string>
#include "log.h"
#include "client_session.h"


std::shared_ptr<net_packet>
net_packet::create(const byte* data, size_t size)
{
    auto np = std::make_shared<net_packet>();

    return np;
}


///////////////////////////////////


int packet_processor::processor_packet(std::shared_ptr<client_session> session)
{
    std::string msg((char*)recv_buf_, recvd_size_);
    session->handle_message(msg);
    recvd_size_ = 0;
    return 0;
}

int standard_packet_processor::processor_packet(std::shared_ptr<client_session> session)
{
    word packet_size = 0;
    tcp_head* head = (tcp_head*)recv_buf_;

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
            auto packet = net_packet::create(&recv_buf_[sizeof(tcp_head)],
                                             packet_size - sizeof(tcp_head));
            if (packet)
            {
                recvd_size_ -= packet_size;
                if (recvd_size_)
                {
                    memmove(recv_buf_, recv_buf_ + packet_size, recvd_size_);
                }
                session->process_packet(head->command.main_cmd_id, head->command.sub_cmd_id, packet);
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
    return 0;
}