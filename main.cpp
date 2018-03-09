#include <iostream>
#include "class/gateway_server.h"


#include <vector>
#include <list>

void test()
{

    std::vector<std::list<int>> dict(10);
    dict[0].push_back(3);
}

int main()
{
#if 1
    gateway_server server;
    server.init();
    server.start();
#else

    test();

#endif


    return 0;
}