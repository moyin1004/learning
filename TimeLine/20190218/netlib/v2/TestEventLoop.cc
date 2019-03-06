/// @file    TestConnection.cc
/// @author  moyin(moyin1004@163.com)
/// @data    2019-02-20 16:53:43
 
#include "Acceptor.h"
#include "EventLoop.h"
#include <unistd.h>
#include <iostream> 

using std::cout;
using std::endl;
using std::string;
 
void test() {
    wd::Acceptor acceptor("192.168.40.128", 8888);
    acceptor.ready();

    wd::EventLoop loop(acceptor);
    loop.loop();
}

int main() {
    test();
    return 0;
}
