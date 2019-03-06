/// @file    TcpServer.cc
/// @author  moyin(moyin1004@163.com)
/// @data    2019-02-23 12:29:37
 
#include "TcpServer.h" 

using std::string;

namespace wd {

TcpServer::TcpServer(const string &ip, unsigned short port)
: _acceptor(ip, port)
, _eventloop(_acceptor)
{}

void TcpServer::start() {
    _acceptor.ready();
    _eventloop.loop();
}

void TcpServer::setConnectionCallback(TcpConnectionCallback && cb) {
    _eventloop.setConnectionCallback(std::move(cb));
}

void TcpServer::setMessageCallback(TcpConnectionCallback && cb) {
    _eventloop.setMessageCallback(std::move(cb));
}

void TcpServer::setCloseCallback(TcpConnectionCallback && cb) {
    _eventloop.setCloseCallback(std::move(cb));
}

} //end of namespace wd
