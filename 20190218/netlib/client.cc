/// @file    tcp_client.cc
/// @author  moyin(moyin1004@163.com)
/// @data    2019-02-13 21:05:24
 
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::string;
using psockaddr = struct sockaddr*;

#define ERROR_EXIT(msg) do{\
    cerr << msg << endl;\
    exit(EXIT_FAILURE);\
} while(0)

void test() {
    int clientfd = socket(AF_INET, SOCK_STREAM, 0);
    if (clientfd == -1) ERROR_EXIT("socket");

    string serverip("192.168.40.128");
    struct sockaddr_in serveraddr;
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(8888);
    serveraddr.sin_addr.s_addr = inet_addr(serverip.data());

    cout << ">> client is about to connect serve..." << endl;
    int ret = connect(clientfd, (psockaddr)&serveraddr, sizeof(serveraddr));
    if (ret == -1) {
        ERROR_EXIT("connect");
        close(clientfd);
    }

    cout << ">>client <----> serve has connected!" << endl;
    cout << "please input data:" << endl;
    string data;
    cin >> data;
    data.push_back('\n');

    ret = send(clientfd, data.c_str(), data.size(), 0);
    if (ret == -1) {
        ERROR_EXIT("send");
        close(clientfd);
    }

    char buff[1024] = {0};
    ret = recv(clientfd, buff, sizeof(buff), 0);
    if (ret == -1) {
        ERROR_EXIT("recv");
        close(clientfd);
        return;
    }
    else if (ret == 0) close(clientfd);
    else {
        cout << ">> client receive " << ret << "bytes data" << endl;
        cout << ">> receivce data: " << buff << endl;
    }

    close(clientfd);
}

int main() {
    test();
    return 0;
}
