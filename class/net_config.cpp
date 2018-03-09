//
// Created by HuanaoGroup on 2018/3/8.
//

#include "net_config.h"


namespace global
{
    boost::asio::io_service g_io_service;
    boost::asio::io_service&
    get_io_service()
    {
        return g_io_service;
    }
}