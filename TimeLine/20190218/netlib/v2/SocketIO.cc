/// @file    SocketIO.cc
/// @author  moyin(moyin1004@163.com)
/// @data    2019-02-19 21:45:29
 
#include "SocketIO.h"
#include "Mylogger.h"
#include <errno.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <iostream>
 
using std::cout;
using std::endl;

namespace wd {

bool SocketIO::isClosed() {
    int nret = 0;
    char buff[1024] = {0};
    do {
        nret = ::recv(_fd, buff, sizeof(buff), MSG_PEEK);
    } while (nret == -1 && errno == EINTR);
    return (nret == 0);
}

int SocketIO::readn(char *buff, int len) {
    char *p = buff;
    int left = len;
    while (left > 0) {
        int ret = ::read(_fd, p, left);
        if (ret == -1 && errno == EINTR) continue;
        else if (ret == -1) {
            logError(">> read");
            return len - left;
        }
        else if (ret == 0) return len - left;
        else if (ret > 0) {
            left -= ret;
            p += ret;
        }
    }
}

int SocketIO::writen(const char *buff, int len) {
    const char *p = buff;
    int left = len;
    while (left > 0) {
        int ret = write(_fd, p, left);
        if (ret == -1 && errno == EINTR) continue;
        else if (ret == -1) {
            logError(">> read");
            return len - left;
        }
        else {
            left -= ret;
            p += ret;
        }
    }
}

int SocketIO::recvPeek(char *buff, int len) {
    int ret = 0;
    do {
        ret = ::recv(_fd, buff, len, MSG_PEEK); //加MSG_PEEK参数，没有移走内核缓冲区的数据
    } while (ret == -1 && errno == EINTR);  //中断情况，重新获取
    return ret;
}

int SocketIO::readline(char *buff, int maxlen) {
    int left = maxlen - 1;
    char *p = buff;
    int total = 0; //记录已从内核缓冲区移走的数据
    while (left > 0) {
        int ret = recvPeek(p, left); //预取。没有移走
        for (size_t i = 0; i < (size_t)ret; ++i) {
            if (p[i] == '\n') {
                int size = i + 1;
                readn(p, size);
                total += size;
                p += size;
                *p = '\0'; //设置用户缓冲区字符串的结尾
                return total;
            }
        }
        readn(p, ret);
        p += ret;
        left -= ret;
        total += ret;
    }
    *p = '\0';
    return total;
}

} //end of namespace wd
