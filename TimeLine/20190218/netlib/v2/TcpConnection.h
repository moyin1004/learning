/// @file    TcpConnection.h
/// @author  moyin(moyin1004@163.com)
/// @data    2019-02-20 16:08:42
 
#ifndef __WD_TCPCONNECTION_H__
#define __WD_TCPCONNECTION_H__
    
#include "Socket.h"
#include "InetAddress.h"
#include "SocketIO.h"

namespace wd {

class TcpConnection {
public:
    explicit
    TcpConnection(int peerfd);
    ~TcpConnection();

    std::string receive();
    void send(const std::string & msg);
    void shutown();
    bool isClosed();

    std::string toString() const;

private:
    InetAddress localInetAddr(); //通过_sock创建的peerfd获取本端地址与端口
    InetAddress peerInetAddr(); //通过_sock创建的peerfd获取对端地址与端口

    Socket _sock;
    InetAddress _localAddr;
    InetAddress _peerAddr;
    SocketIO _socketIO;
    bool _isShutdownWrite;   //主动关闭写端连接
};

} //end of namespace wd

#endif
