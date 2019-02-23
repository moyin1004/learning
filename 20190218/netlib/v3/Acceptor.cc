/// @file    Acceptor.cc
/// @author  moyin(moyin1004@163.com)
/// @data    2019-02-19 23:11:59
 
#include "Acceptor.h"
#include "Mylogger.h"
 
namespace wd {

Acceptor::Acceptor(const std::string &ip, unsigned short port) 
: _sock()
, _addr(ip, port)
{}

Acceptor::Acceptor(unsigned short port)
: _sock()
, _addr(port)
{}

void Acceptor::ready() {
    setReuseAddr();
    setReusePort();
    bind();
    listen();
}

int Acceptor::accept() {
    int peerfd = ::accept(fd(), nullptr, nullptr);
    if (peerfd == -1) {
        logError(">> accept");
    }
    return peerfd;
}

int Acceptor::fd() const {
    return _sock.fd();
}

void Acceptor::setReuseAddr() {
    int reuse = 1;
    //将socket成可以重用的
    if (setsockopt(fd(), SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(int))) {
        logError(">> setsockopt");
    }
}

void Acceptor::setReusePort() {
    int reuse = 1;
    //端口设置成可以重用的
    if (setsockopt(fd(), SOL_SOCKET, SO_REUSEPORT, &reuse, sizeof(int))) {
        logError(">> setsockopt");
    }
}

void Acceptor::bind() {
    int ret = ::bind(fd(),
                     (const struct sockaddr *)_addr.getSockaddrPtr(),
                     sizeof(InetAddress));
    if (ret == -1) logError(">> bind");
}

void Acceptor::listen() {
    int ret = ::listen(fd(), 10);
    if (ret == -1) logError(">> listen");
}

} //end of namespace wd
