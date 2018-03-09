//
// Created by HuanaoGroup on 2018/3/7.
//

#ifndef GATEWAY_DATA_TRANSFER_MANAGER_H
#define GATEWAY_DATA_TRANSFER_MANAGER_H

#include <boost/asio.hpp>

class tcp_acceptor;
class client_session_manager;
class client_data_processor;

class data_transfer_manager
{
public:
    data_transfer_manager(boost::asio::io_service& io_service);

    void start();

private:

    std::shared_ptr<tcp_acceptor> acceptor_;
//    std::shared_ptr<client_session_manager> session_manager_;
    std::shared_ptr<client_data_processor> client_processor_;
};


#endif //GATEWAY_DATA_TRANSFER_MANAGER_H
