/// @file    Socket.h
/// @author  moyin(moyin1004@163.com)
/// @data    2019-02-18 22:32:35
 
#ifndef __WD_SOCKET_H__
#define __WD_SOCKET_H__

namespace wd {

class Socket {
public:
    Socket();
    explicit Socket(int);

    ~Socket();
    int fd() const;
    void nonblock();
    void shutdownWrite();

private:
    int _fd;
};

} //end of namespace

#endif
