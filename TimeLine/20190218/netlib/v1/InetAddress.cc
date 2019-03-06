/// @file    InetAddress.cc
/// @author  moyin(moyin1004@163.com)
/// @data    2019-02-19 20:23:48
 
#include "InetAddress.h"
#include "Mylogger.h"
#include <string.h>
#include <arpa/inet.h>
 
using std::string;

namespace wd {

InetAddress::InetAddress(const string &ip, unsigned short port) {
    ::memset(&_addr, 0, sizeof(struct sockaddr_in));
    _addr.sin_family = AF_INET;
    _addr.sin_port = htons(port);
    _addr.sin_addr.s_addr = inet_addr(ip.data());
}

InetAddress::InetAddress(unsigned short port) {
    ::memset(&_addr, 0, sizeof(struct sockaddr_in));
    _addr.sin_family = AF_INET;
    _addr.sin_port = htons(port);
    _addr.sin_addr.s_addr = INADDR_ANY; //本机地址
}

InetAddress::InetAddress(const struct sockaddr_in & addr) 
: _addr(addr)
{}

string InetAddress::ip() const {
    return string(inet_ntoa(_addr.sin_addr));
}

unsigned short InetAddress::port() const {
    return ntohs(_addr.sin_port);
}

struct sockaddr_in *InetAddress::getSockaddrPtr() {
    return &_addr;
}

} //end of namespace wd
