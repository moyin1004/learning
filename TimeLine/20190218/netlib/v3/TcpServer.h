/// @file    TcpServer.h
/// @author  moyin(moyin1004@163.com)
/// @data    2019-02-23 12:29:18
 
#ifndef __TCPSERVER_H__
#define __TCPSERVER_H__
    
#include "Acceptor.h"
#include "EventLoop.h"

namespace wd {

class TcpServer {
public:
    using TcpConnectionCallback =
        std::function<void(const std::shared_ptr<TcpConnection>)>;
    TcpServer(const std::string &ip, unsigned short port);
    void start();

    void setConnectionCallback(TcpConnectionCallback && cb);
    void setMessageCallback(TcpConnectionCallback && cb);
    void setCloseCallback(TcpConnectionCallback && cb);

private:
    Acceptor _acceptor;
    EventLoop _eventloop;
};

} //end of namespace wd

#endif
