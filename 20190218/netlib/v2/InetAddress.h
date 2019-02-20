/// @file    InetAddress.h
/// @author  moyin(moyin1004@163.com)
/// @data    2019-02-18 23:26:08
 
#ifndef __WD_INETADDRESS_H__
#define __WD_INETADDRESS_H__

#include <netinet/in.h>
#include <string>

namespace wd {

class InetAddress {
public:
    InetAddress(const std::string & ip, unsigned short port);
    InetAddress(unsigned short port);
    InetAddress(const struct sockaddr_in & addr);

    std::string ip() const;
    unsigned short port() const;
    struct sockaddr_in *getSockaddrPtr();

private:
    struct sockaddr_in _addr;
};

} //end of namespace wd
    
#endif
