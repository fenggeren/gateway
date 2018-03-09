//
// Created by HuanaoGroup on 2018/3/9.
//

#include "net_packet.h"


std::shared_ptr<net_packet>
net_packet::create(const byte* data, size_t size)
{
    auto np = std::make_shared<net_packet>();

    return np;
}