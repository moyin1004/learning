/// @file    SendThread.h
/// @author  moyin(moyin1004@163.com)
/// @data    2019-02-19 18:29:52
 
#ifndef __SENDTHREAD_H__
#define __SENDTHREAD_H__

#include "Thread.h"
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <iostream>

class SendThread
: public wd::Thread
{
public:
    SendThread(int peerfd)
    : _peerfd(peerfd)
    {}

    void run() {
        while (true) {
            char buff[1024] = {0};
            std::cin >> buff;
            std::cout << "send before" << std::endl;
            int ret = send(_peerfd, buff, strlen(buff), 0);
            if (ret == -1) {
                std::cerr << "send" << std::endl;;
                close(_peerfd);
            }
        }
    }

private:
    int _peerfd;
};

#endif
