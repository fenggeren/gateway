//
// Created by HuanaoGroup on 2018/3/7.
//

#ifndef GATEWAY_CLIENT_DATA_PROCESSOR_H
#define GATEWAY_CLIENT_DATA_PROCESSOR_H

#include <memory>

class client_session;
class client_session_manager;


class client_acceptor
{
public:
    ~client_acceptor(){}

    virtual void accept_session(std::shared_ptr<client_session> session) = 0;

    virtual void accept_data(std::shared_ptr<client_session> session) = 0;
};



class client_data_processor : public client_acceptor
{
public:

    client_data_processor();

    virtual void accept_session(std::shared_ptr<client_session> session) override ;

    virtual void accept_data(std::shared_ptr<client_session> session) override ;

private:

    std::shared_ptr<client_session_manager> session_manager_;
};


#endif //GATEWAY_CLIENT_DATA_PROCESSOR_H
