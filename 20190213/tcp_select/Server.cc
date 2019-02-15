/// @file    Server.cc
/// @author  moyin(moyin1004@163.com)
/// @data    2019-02-14 19:42:10

#include "Server.h"
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/select.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <unordered_set>
 
using std::cout;
using std::endl;
using std::cerr;
using std::string;
using std::unordered_set;

#define ERROR_EXIT(msg) do{\
    cerr << msg << endl;\
    exit(EXIT_FAILURE);\
} while(0)

namespace wd {

Server::Server()
: _listenfd(-1)
{
    _listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (_listenfd == -1) ERROR_EXIT("socket");
}

void Server::setReuseAddr(int on) {
    int reuse = on;
    //将网络地址设置成可以重用的
    if (setsockopt(_listenfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(int))) {
        ERROR_EXIT("setsockopt");
    }
}

void Server::setReusePort(int on) {
    int reuse = on;
    //端口设置成可以重用的
    if (setsockopt(_listenfd, SOL_SOCKET, SO_REUSEPORT, &reuse, sizeof(int))) {
        ERROR_EXIT("setsockopt");
    }
}

void Server::startServer(const string &ip, unsigned short port) {
    cout << ">> server listened = " << _listenfd << endl;
    setReuseAddr(1);
    setReusePort(1);
    
    bindInetAddr(_listenfd, ip, port);
    myListen(_listenfd);
}

void Server::selectServe() {
    fd_set rfds;
    struct timeval tv;  //设置等待时间，这个时间后返回一次
    int maxfd = 1024;

    while(true) {
        FD_ZERO(&rfds);
        FD_SET(_listenfd, &rfds);

        selectFdsInit(maxfd, &rfds);
        tv.tv_sec = 5;
        tv.tv_usec = 0;

        //int ready = select(maxfd, &rfds, nullptr, nullptr, nullptr);
        int ready = select(maxfd + 1, &rfds, nullptr, nullptr, &tv);
        cout << ">> select retval = " << ready << endl;
        if (ready == -1 && errno == EINTR) {
            continue;
        }
        else if (ready == -1) ERROR_EXIT("select");
        else if (ready == 0) {
            cout << ">> select timeout!" << endl;
            continue;
        }
        else {
            for (int fd = 0; fd < maxfd + 1; ++fd) {
                if (FD_ISSET(fd, &rfds) && fd == _listenfd) {
                    int peerfd = handleNewConnection(_listenfd);
                    setNonBlock(peerfd);
                    printConnectionInfo(peerfd);
                    cout << "has connected!" << endl;
                    FD_SET(peerfd, &rfds);
                    _client_fds.insert(peerfd);
                }
                if (FD_ISSET(fd, &rfds) && fd != _listenfd) {
                    cout << "fd = " << fd << endl;
                    handleClientMsg(fd, &rfds);
                }
            }
        }
        cout << endl;
    } //end of while
    FD_CLR(_listenfd, &rfds);
    close(_listenfd);
}

void Server::setNonBlock(int fd) {
    int flags = fcntl(fd, F_GETFL, 0);
    if (flags == -1) ERROR_EXIT("fcntl");
    int ret = fcntl(fd, F_SETFL, O_NONBLOCK | flags);
    if (ret == -1) ERROR_EXIT("fcnt1");
}

void Server::printConnectionInfo(int peerfd) {
    struct sockaddr_in serveraddr;
    socklen_t len = sizeof(serveraddr);
    int ret = getsockname(peerfd, (psockaddr)&serveraddr, &len);

    struct sockaddr_in clientaddr;
    ret = getpeername(peerfd, (psockaddr)&clientaddr, &len);
    if (ret == -1) cerr << "getpeername" << endl;
    else {
        string serverip(inet_ntoa(serveraddr.sin_addr));
        unsigned short serverport = ntohs(serveraddr.sin_port);

        string clientip(inet_ntoa(clientaddr.sin_addr));
        unsigned short clientport = ntohs(clientaddr.sin_port);

        cout << ">> server " << serverip << ":" << serverport << " --> "
             << "client " << clientip << ":" << clientport << endl; 
    }
}

int Server::bindInetAddr(int fd, const string &ip, unsigned short port) {
    struct sockaddr_in serveraddr;
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(port);
    inet_aton(ip.data(), &serveraddr.sin_addr);

    int ret = bind(fd ,(psockaddr)&serveraddr, sizeof(serveraddr));
    if (ret == -1) {
        close(fd);
        ERROR_EXIT("bind");
    }
    return ret;
}

int Server::myListen(int fd) {
    int ret = ::listen(fd, 10);
    if (ret == -1) {
        close(fd);
        ERROR_EXIT("listen");
    }
    return ret;
}

int Server::myAccept(int fd) {
    int peerfd = accept(fd, nullptr, nullptr);
    if (peerfd == -1) {
        close(fd);
        ERROR_EXIT("accept");
    }
    return peerfd;
}

int Server::handleNewConnection(int listenfd) {
    cout << ">> server is about to accpet a new link" << endl;
    int peerfd = myAccept(listenfd);
    cout << ">> server server client with fd = " << peerfd << endl;
    return peerfd;
}

void Server::handleClientMsg(int peerfd, fd_set *rfds) {
    char buff[1024] = {0};
    cout << ">> before recv " << endl;
    int ret = recv(peerfd, buff, sizeof(buff), 0); //默认为阻塞式函数
    cout << "server recv ret = " << ret << endl;
    if (ret < 0) {
        if (ret == -1 && errno == EINTR) //errno == EINTR 中断
            return; 
        else
            cerr << ">> no recv" << endl;
            //ERROR_EXIT("revc"); //设置为非阻塞式，这里会退出
    }
    else if (ret == 0) {
        printConnectionInfo(peerfd);
        cout << " has closed!!!" << endl;
        close(peerfd);
        FD_CLR(peerfd, rfds);
        _client_fds.erase(peerfd);
    }
    else {
        cout << ">> server got msg from client: " << buff << endl;
        ret = send(peerfd, buff, strlen(buff), 0);
        if (ret == -1) {
            cerr << "send" << endl;;
            close(peerfd);
        }
    }
}

void Server::selectFdsInit(int &maxfd, fd_set * rfds) {
    for (auto & fd : _client_fds) {
        FD_SET(fd, rfds);
        if (maxfd < fd) maxfd = fd;
    }
}

} //end of namespce wd
