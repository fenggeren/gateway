//
// Created by HuanaoGroup on 2018/3/9.
//

#include "net_packet.h"
#include <string>
#include "log.h"
#include "client_session.h"

std::shared_ptr<net_packet> create_packet(const byte* data, size_t size)
{
    auto np = std::make_shared<net_packet>(data, size);

    return np;
}

net_packet::net_packet(const byte *data, size_t size)
: buffer_(new byte[size]),
  size_(size)
{
    memcpy(buffer_, data, size);
}

net_packet::~net_packet()
{
    if (buffer_)
    {
        delete []buffer_;
    }
    buffer_ = nullptr;
}

//std::shared_ptr<net_packet>
//net_packet::create(const byte* data, size_t size)
//{
//    auto np = std::make_shared<net_packet>(data, size);
//
//    return np;
//}

