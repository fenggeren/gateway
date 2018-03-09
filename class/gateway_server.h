//
// Created by HuanaoGroup on 2018/3/6.
//

#ifndef GATEWAY_GATEWAY_SERVER_H
#define GATEWAY_GATEWAY_SERVER_H

#include <memory>

class data_transfer_manager;

class gateway_server
{
public:

    gateway_server();

    void init();

    void start();

private:
    std::shared_ptr<data_transfer_manager> data_transfer_manager_;
};


#endif //GATEWAY_GATEWAY_SERVER_H
