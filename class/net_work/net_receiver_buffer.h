//
// Created by HuanaoGroup on 2018/3/7.
//

#ifndef GATEWAY_NET_RECEIVER_BUFFER_H
#define GATEWAY_NET_RECEIVER_BUFFER_H


#include <memory>
#include <boost/system/error_code.hpp>
#include "net_packet_config.h"

class client_session;
class net_packet;
class receive_packet_processor;

class net_receiver_buffer : public std::enable_shared_from_this<net_receiver_buffer>
{
public:

    net_receiver_buffer(std::shared_ptr<client_session> session);

    ~net_receiver_buffer();

    void start_async_read();

    void handle_read(const boost::system::error_code& ec, size_t bytes_transferred);

    void handle_message(const std::string& msg);


private:

    void scan_packets();

private:
    byte* recv_buf_;
    size_t recvd_size_;

    std::weak_ptr<client_session> session_;
    std::shared_ptr<receive_packet_processor> packet_processor_;
};


#endif //GATEWAY_NET_RECEIVER_BUFFER_H
