/// @file    TcpConnection.h
/// @author  moyin(moyin1004@163.com)
/// @data    2019-02-20 16:08:42
 
#ifndef __WD_TCPCONNECTION_H__
#define __WD_TCPCONNECTION_H__
    
#include "Socket.h"
#include "InetAddress.h"
#include "SocketIO.h"
#include "Noncopyable.h"
#include <functional>
#include <memory>

namespace wd {

class EventLoop;

class TcpConnection 
: Noncopyable
, public std::enable_shared_from_this<TcpConnection>
{
public:
    using TcpConnectionCallback = 
        std::function<void(const std::shared_ptr<TcpConnection> &) >;

    explicit
    TcpConnection(int peerfd, EventLoop &loop);
    ~TcpConnection();

    std::string receive();
    void send(const std::string &msg);
    void sendInLoop(const std::string &msg); //把send函数和计算线程处理后的数据注册给EventLoop
    void shutown();
    bool isClosed();
    std::string toString() const;

    void setConnectionCallback(TcpConnectionCallback && cb) //注册回调函数终点
    {   _onConnectionCallback = std::move(cb);  }

    void setMessageCallback(TcpConnectionCallback && cb)
    {   _onMessageCallback = std::move(cb); }

    void setCloseCallback(TcpConnectionCallback && cb)
    {   _onCloseCallback = std::move(cb);   }

    void handleConnectionCallback();
    void handleMessageCallback();
    void handleCloseCallback();

private:
    InetAddress localInetAddr(); //通过_sock创建的peerfd获取本端地址与端口
    InetAddress peerInetAddr(); //通过_sock创建的peerfd获取对端地址与端口

private:
    Socket _sock;
    InetAddress _localAddr;
    InetAddress _peerAddr;
    SocketIO _socketIO;
    bool _isShutdownWrite;   //主动关闭写端连接

    TcpConnectionCallback _onConnectionCallback;
    TcpConnectionCallback _onMessageCallback;
    TcpConnectionCallback _onCloseCallback;
    EventLoop &_loop;
};

} //end of namespace wd

#endif
