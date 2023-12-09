/// @file    Server.h
/// @author  moyin(moyin1004@163.com)
/// @data    2019-02-14 19:21:28

#ifndef __SERVER_H__
#define __SERVER_H__

#include <sys/socket.h>
#include <sys/types.h>

#include <string>
#include <unordered_set>

namespace wd {

class Server {
public:
    Server();
    using psockaddr = struct sockaddr *;

    void startServer(const std::string &, unsigned short);
    void pollServe();  // 并发服务器模型之IO复用poll

private:
    void selectFdsInit(int &, fd_set *);  // 初始化fd_set集合
    void setReuseAddr(int on);            // 设置网络地址重用
    void setReusePort(int on);            // 设置端口复用
    void setNonBlock(int fd);
    void printConnectionInfo(int peerfd);

    int bindInetAddr(int fd, const std::string &, unsigned short);
    int myListen(int);
    int myAccept(int fd);
    int handleNewConnection(int listenfd);
    void handleClientMsg(int peerfd, pollfd *rfds);

private:
    int _listenfd;
    std::unordered_set<int> _client_fds;
};

}  // end of namespace wd

#endif
