//
// Created by HuanaoGroup on 2018/3/12.
//

#ifndef GATEWAY_RECEIVE_PACKET_PROCESSOR_H
#define GATEWAY_RECEIVE_PACKET_PROCESSOR_H


#include "net_packet_config.h"
#include "net_packet.h"

class receive_packet_processor
{
public:

    receive_packet_processor(byte*& recv_buf, size_t& size)
            :recv_buf_(recv_buf),
             recvd_size_(size)
    {

    }

    ~receive_packet_processor(){}

    // 给定数据， 创建数据包结构
    virtual int processor_packet(std::shared_ptr<client_session> session);

protected:
    byte* &recv_buf_;
    size_t &recvd_size_;
};

class standard_receive_packet_processor : public receive_packet_processor
{
public:
    standard_receive_packet_processor(byte*& recv_buf, size_t& size):
            receive_packet_processor(recv_buf, size)
    {

    }

    virtual int processor_packet(std::shared_ptr<client_session> session);
};



#endif //GATEWAY_RECEIVE_PACKET_PROCESSOR_H
