/// @file    tcp_server.cc
/// @author  moyin(moyin1004@163.com)
/// @data    2019-02-12 23:28:44
 
#include "Server.h"
#include <iostream>
#include <string>

using namespace wd;
using std::cout;
using std::endl;
using std::string;
 
void test() {
    string ip("192.168.40.128");
    unsigned short port = 8888;
    Server server;
    server.startServer(ip, port);
    server.selectServe();
}

int main() {
    test();
    return 0;
}
