//
// Created by HuanaoGroup on 2018/3/6.
//

#ifndef GATEWAY_CLIENT_SESSION_H
#define GATEWAY_CLIENT_SESSION_H

#include <boost/asio.hpp>
#include "net_packet_config.h"

using boost::asio::ip::tcp;

class net_receiver_buffer;
class net_send_buffer;
class client_acceptor;
class net_packet;


class client_session : public std::enable_shared_from_this<client_session>
{
public:
    client_session(tcp::socket socket, std::shared_ptr<client_acceptor> accptor);

    ~client_session();

    std::string get_remote_ipaddress() const;

    tcp::socket& get_socket();

    void handle_message(const std::string& msg);

    void start_async_read();

    std::shared_ptr<net_receiver_buffer> get_receiver_buffer();
    std::shared_ptr<net_send_buffer> get_send_buffer();


    // 接受数据包
    void receive_packet(word main_id, word sub_id, std::shared_ptr<net_packet> packet);

    // 发送数据包
    void send_packet(word main_id, word sub_id, std::shared_ptr<net_packet> packet);

    void close();
private:
    tcp::socket socket_;
    std::shared_ptr<net_receiver_buffer> receiver_buffer_;
    std::shared_ptr<net_send_buffer> send_buffer_;
    std::weak_ptr<client_acceptor> client_acceptor_;
};


#endif //GATEWAY_CLIENT_SESSION_H
