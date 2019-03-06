/// @file    Socket.cc
/// @author  moyin(moyin1004@163.com)
/// @data    2019-02-18 22:36:31
 
#include "Mylogger.h"
#include "Socket.h"
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/types.h>

namespace wd {

Socket::Socket() {
    _fd = ::socket(AF_INET, SOCK_STREAM, 0);
    if (_fd == -1) {
        logError("socket create error");
    }
    logDebug(">> socket create");
}

Socket::Socket(int fd)
: _fd(fd)
{
    logDebug("Socket::Socket(int)");
}

Socket::~Socket() {
    logDebug("Socket::~Socket()");
    ::close(_fd);
}

int Socket::fd() const {
    return _fd;
}

void Socket::nonblock() {
    int flag = ::fcntl(_fd, F_GETFL, 0);
    if (flag == -1) logError("fcntl");
    int ret = ::fcntl(_fd, F_SETFL, O_NONBLOCK | flag);
    if (ret == -1) logError("fcntl");
}

void Socket::shutdownWrite() {
    if (::shutdown(_fd, SHUT_WR)) {
        logError("shutdownWrite()");
    }
}

} //end of namespace wd
