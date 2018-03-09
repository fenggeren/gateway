//
// Created by HuanaoGroup on 2018/3/6.
//

#ifndef GATEWAY_TCP_ACCEPTOR_H
#define GATEWAY_TCP_ACCEPTOR_H

#include <boost/asio.hpp>

using tcp = boost::asio::ip::tcp;
class client_acceptor;

class tcp_acceptor
{
public:

    tcp_acceptor(boost::asio::io_service& io_service, short port)
            : acceptor_(io_service, tcp::endpoint(tcp::v4(),port)),
              socket_(io_service)
    {

    }

    void start(std::shared_ptr<client_acceptor> accptor);

private:

    void do_accept(std::shared_ptr<client_acceptor> accptor);

private:
    tcp::acceptor acceptor_;
    tcp::socket socket_;
};


#endif //GATEWAY_TCP_ACCEPTOR_H
