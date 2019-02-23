/// @file    SocketIO.h
/// @author  moyin(moyin1004@163.com)
/// @data    2019-02-19 21:40:06
 
#ifndef __WD_SOCKETIO_H__
#define __WD_SOCKETIO_H__

namespace wd {

class SocketIO {
public:
    explicit
    SocketIO(int fd) : _fd(fd) {};

    bool isClosed();

    int readn(char *buff, int len); //接收len字节的数据
    int writen(const char *buff, int len); //发送len字节的数据

    int readline(char *buff, int len); //接收一行数据，'\n'数据结尾
private:
    int recvPeek(char *buff, int len);

    int _fd;
};

} //end of namespace
    
#endif
