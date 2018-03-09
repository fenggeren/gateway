//
// Created by HuanaoGroup on 2018/3/6.
//

#include "gateway_server.h"
#include "data_transfer_manager.h"
#include "net_config.h"
#include "timer_manager.h"


timer_manager *g_timer_manager = nullptr;

gateway_server::gateway_server()
{

}

void gateway_server::init()
{
    auto& io_service = global::get_io_service();

    timer_manager tm(io_service);
    g_timer_manager = &tm;

    data_transfer_manager_ = std::make_shared<data_transfer_manager>(io_service);
}


void gateway_server::start()
{
    data_transfer_manager_->start();

    auto& io_service = global::get_io_service();

    io_service.run();
}