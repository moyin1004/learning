/// @file    TcpConnection.cc
/// @author  moyin(moyin1004@163.com)
/// @data    2019-02-20 16:08:36
 
#include "TcpConnection.h"
#include "Mylogger.h"
#include <sys/socket.h>
#include <iostream>
#include <sstream>

using std::cout;
using std::endl;
using std::string;

namespace wd {

TcpConnection::TcpConnection(int peerfd)
: _sock(peerfd)
, _localAddr(localInetAddr())
, _peerAddr(peerInetAddr())
, _socketIO(peerfd)
, _isShutdownWrite(false)
{}

TcpConnection::~TcpConnection() {
    shutown();
    cout << toString() << " has closed" << endl;
}

string TcpConnection::receive() {
    char buff[10240] = {0};
    int ret = _socketIO.readline(buff, sizeof(buff));
    if (ret <= 0) return string();
    else return string(buff);
}

void TcpConnection::send(const string & msg) {
    int ret = _socketIO.writen(msg.data(), msg.size());
    if (ret != static_cast<int>(msg.size())) logInfo("send msg error"); 
}

void TcpConnection::shutown() { //主动关闭写端连接
    if (!_isShutdownWrite) {
        _sock.shutdownWrite();
        _isShutdownWrite = true;
    }
}

string TcpConnection::toString() const {
    std::ostringstream oss;
    oss << _localAddr.ip() << ":" << _localAddr.port() << "-->"
        << _peerAddr.ip() << ":" << _peerAddr.port();
    return oss.str();
}

InetAddress TcpConnection::localInetAddr() {
    struct sockaddr_in localaddr;
    socklen_t len = sizeof(struct sockaddr_in);
    int ret = ::getsockname(_sock.fd(), (struct sockaddr*)&localaddr, &len);
    if (ret == -1) logError(">> getsockname");
    return InetAddress(localaddr);
}

InetAddress TcpConnection::peerInetAddr() {
    struct sockaddr_in peeraddr;
    socklen_t len = sizeof(struct sockaddr_in);
    int ret = ::getpeername(_sock.fd(), (struct sockaddr*)&peeraddr, &len);
    if (ret == -1) logError(">> getpeername");
    return InetAddress(peeraddr);
}

} //end of namespace wd
