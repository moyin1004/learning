/// @file    tcp_server.cc
/// @author  moyin(moyin1004@163.com)
/// @data    2019-02-12 23:28:44
 
#include "Thread.h"
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <functional>
#include <vector>
#include <string>
#include <memory>

using namespace wd;
using std::cout;
using std::endl;
using std::cerr;
using std::string;
using std::vector;
using std::shared_ptr;
using psockaddr = struct sockaddr*;
 
#define ERROR_EXIT(msg) do{\
    cerr << msg << endl;\
    exit(EXIT_FAILURE);\
} while(0)

class ServerThread
: public Thread
{
public:
    ServerThread(int peerfd,string ip, unsigned short port)
    : _peerfd(peerfd)
    , _ip(ip)
    , _port(port)
    {}

    ~ServerThread() {}

    void run() {
        cout << "main thread create subthread : " << pthread_self() << endl;
        struct sockaddr_in clientaddr;
        socklen_t len = sizeof(clientaddr);
        int ret = getpeername(_peerfd, (psockaddr)&clientaddr, &len);
        if (ret == -1) cerr << "getpeername" << endl;
        else {
            string clientip(inet_ntoa(clientaddr.sin_addr));
            unsigned short clientport = ntohs(clientaddr.sin_port);
            cout << ">> server " << _ip << ":" << _port << " --> "
                 << "client " << clientip << ":" << clientport 
                 << " has connected!" << endl;
        }

        //数据接收
        char buff[1024] = {0};
        cout << ">> before recv " << endl;
        ret = recv(_peerfd, buff, sizeof(buff), 0); //默认为阻塞式函数
        cout << "server recv ret = " << ret << endl;
        if (ret < 0) {
            if (ret == -1 && errno == EINTR) //errno == EINTR 中断
                return; 
            else
                ERROR_EXIT("revc");
        }
        else if (ret == 0) close(_peerfd);
        else {
            cout << ">> server got msg from client: " << buff << endl;
            ret = send(_peerfd, buff, strlen(buff), 0);
            if (ret == -1) {
                ERROR_EXIT("send");
                close(_peerfd);
            }
            sleep(1);
            close(_peerfd);
        }
    }
private:
    int _peerfd;
    string _ip;
    unsigned short _port;
};

void test() {
    int listenfd = socket(AF_INET, SOCK_STREAM, 0); //tcp协议 IPV4 文件描述符
    if (listenfd == -1) ERROR_EXIT("socket");

    unsigned short port = 8888;
    string ip("192.168.40.128");
    struct sockaddr_in serveraddr;
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(port);
    inet_aton(ip.data(), &serveraddr.sin_addr);
    //serveraddr.sin_addr.s_addr = inet_addr(ip.data()); //功能同上一行

    if (-1 == bind(listenfd,
            (const struct sockaddr *)&serveraddr,
            sizeof(serveraddr)))
    {  ERROR_EXIT("bind");  }

    //设置处于半连接状态的连接数的最大值
    if (-1 == listen(listenfd, 10)) ERROR_EXIT("bind");

    //并发服务器模型之多线程模型
    vector<shared_ptr<Thread>> pthreads;
    while (1) {
        cout << ">> server is about to accpet a new link" << endl;

        //建立连接
        int peerfd = accept(listenfd, nullptr, nullptr);
        if (peerfd == -1) {
            close(listenfd);
            ERROR_EXIT("accept");
        }

        cout << ">> serve serve client with peerfd = " << peerfd << endl;
        shared_ptr<Thread> pthid(new ServerThread(peerfd, ip, port));
        pthid->start();
        pthreads.push_back(pthid);
    } //end of while

    cout << ">> main thread release subthreads..." << endl;
    for(auto & pthid : pthreads) pthid->join();

    close(listenfd); //文件描述符资源有限
}

int main() {
    test();
    return 0;
}
