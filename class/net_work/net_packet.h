//
// Created by HuanaoGroup on 2018/3/9.
//

#ifndef GATEWAY_NET_PACKET_H
#define GATEWAY_NET_PACKET_H

#include <cstddef>
#include <memory>
#include "net_packet_config.h"

class net_packet
{
public:
//    virtual void init(const byte* data, size_t size) = 0;

    static std::shared_ptr<net_packet> create(const byte* data, size_t size);

private:

};

class net_packet_factory
{
public:

};


#endif //GATEWAY_NET_PACKET_H
