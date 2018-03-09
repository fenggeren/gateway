//
// Created by HuanaoGroup on 2018/3/7.
//

#ifndef GATEWAY_GLOBAL_H
#define GATEWAY_GLOBAL_H

#include <boost/asio.hpp>


namespace global
{
    boost::asio::io_service& get_io_service();
}


#endif //GATEWAY_GLOBAL_H
