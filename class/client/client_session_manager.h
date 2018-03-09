//
// Created by HuanaoGroup on 2018/3/7.
//

#ifndef GATEWAY_CLIENT_SESSION_MANAGER_H
#define GATEWAY_CLIENT_SESSION_MANAGER_H


#include <memory>

class client_session;
class circle_sessions;


class client_session_manager
{
public:

    client_session_manager();

    void add_session(std::shared_ptr<client_session> session);

    void update_session(std::shared_ptr<client_session> session);

private:

//    std::vector<std::list<std::shared_ptr<client_session>>> circle_sessions_;
    std::shared_ptr<circle_sessions> circle_sessions_;
};


#endif //GATEWAY_CLIENT_SESSION_MANAGER_H
