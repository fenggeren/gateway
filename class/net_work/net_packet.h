//
// Created by HuanaoGroup on 2018/3/9.
//

#ifndef GATEWAY_NET_PACKET_H
#define GATEWAY_NET_PACKET_H

#include <cstddef>
#include <memory>
#include <string>

#include "net_packet_config.h"

class client_session;
class net_packet;


std::shared_ptr<net_packet>
create_packet(const byte* data, size_t size);


class net_packet
{
public:

    net_packet(const byte* data, size_t size);

    virtual ~net_packet();

//    static std::shared_ptr<net_packet> create(const byte* data, size_t size);

    const byte* get_buffer() const
    {
        return buffer_;
    }

    const size_t get_size() const
    {
        return size_;
    }


protected:
    byte* buffer_;
    size_t size_;
};

class net_msg_packet
{
public:
    net_msg_packet(const byte* data, size_t size):
            msg_((const char*)data, size)
    {

    }

private:
    std::string msg_;
};







#endif //GATEWAY_NET_PACKET_H
