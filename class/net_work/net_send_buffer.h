//
// Created by HuanaoGroup on 2018/3/10.
//

#ifndef GATEWAY_NET_SEND_BUFFER_H
#define GATEWAY_NET_SEND_BUFFER_H


#include <cstdio>
#include "net_packet_config.h"
#include "client_session.h"


class send_packet_processor;

class net_send_buffer
{
public:

    net_send_buffer(std::shared_ptr<client_session> session);

    ~net_send_buffer();

    void send_data(const byte* data, size_t size);

    void send_packet(word main_id, word sub_id, std::shared_ptr<net_packet> packet);

    void send_after_close();
private:

    void processor_data(const byte* buffer, size_t size);

    void async_send_data(std::shared_ptr<client_session> session);

    size_t get_send_buffer_left() const
    {
        int left = send_buf_allocated_ - send_buffer_used_;
        return left < 0 ? 0 : (size_t)left;
    }

    bool realloc_send_buffer();

private:
    byte* send_buffer_;
    byte* cur_write_buffer_;

    size_t send_buffer_used_;
    size_t cur_write_buffer_used_;

    size_t send_buf_allocated_;
    size_t cur_write_buffer_allocated_;


    bool close_after_send_;

    std::weak_ptr<client_session> client_session_;
    std::shared_ptr<send_packet_processor> send_processor_;
};


#endif //GATEWAY_NET_SEND_BUFFER_H
