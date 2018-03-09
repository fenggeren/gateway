//
// Created by HuanaoGroup on 2018/3/9.
//

#ifndef GATEWAY_NET_PACKET_H
#define GATEWAY_NET_PACKET_H

#include <cstddef>
#include <memory>
#include "net_packet_config.h"

class client_session;

class net_packet
{
public:
//    virtual void init(const byte* data, size_t size) = 0;

    static std::shared_ptr<net_packet> create(const byte* data, size_t size);

private:
    tcp_head head_;
};







class packet_processor
{
public:

    packet_processor(byte*& recv_buf, size_t& size)
            :recv_buf_(recv_buf),
             recvd_size_(size)
    {

    }

    ~packet_processor(){}

    // 给定数据， 创建数据包结构
    virtual int processor_packet(std::shared_ptr<client_session> session);

protected:
    byte* &recv_buf_;
    size_t &recvd_size_;
};

class standard_packet_processor : public packet_processor
{
public:
    standard_packet_processor(byte*& recv_buf, size_t& size):
            packet_processor(recv_buf, size)
    {}

    virtual int processor_packet(std::shared_ptr<client_session> session);
};




#endif //GATEWAY_NET_PACKET_H
