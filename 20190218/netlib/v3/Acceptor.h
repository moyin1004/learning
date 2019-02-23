/// @file    Acceptor.h
/// @author  moyin(moyin1004@163.com)
/// @data    2019-02-19 23:11:01
 
#ifndef __WD_ACCEPTOR_H__
#define __WD_ACCEPTOR_H__
    
#include "Socket.h"
#include "InetAddress.h"

namespace wd {

class Acceptor {
public:
    Acceptor(const std::string &ip, unsigned short port);
    Acceptor(unsigned short port);

    void ready();
    int accept();
    int fd() const;

private:
    void setReuseAddr(); //设置socket重用
    void setReusePort(); //设置端口重用
    void bind();
    void listen();

    Socket _sock;
    InetAddress _addr;
};

} //end of namespace wd

#endif
