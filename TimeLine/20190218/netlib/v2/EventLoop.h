/// @file    EventLoop.h
/// @author  moyin(moyin1004@163.com)
/// @data    2019-02-20 17:30:23
 
#ifndef __EVENTLOOP_H__
#define __EVENTLOOP_H__

#include <sys/epoll.h>
#include <vector>
#include <map>
#include <memory>

namespace wd {

class Acceptor;
class TcpConnection;
class EventLoop {
public:
    EventLoop(Acceptor &acceptor);
    ~EventLoop();

    void loop();
    void unloop();

private:
    int creatEpollFd();
    void addEpollReadFd(int fd);
    void delEpollReadFd(int fd);

    void waitEpollFds();
    void handleNewConnection();
    void handleMessage(int peerfd);

private:
    int _eventfd;
    Acceptor &_acceptor;
    std::map<int, std::shared_ptr<TcpConnection>> _connections;
    std::vector<struct epoll_event> _eventList;
    bool _isLooping;
};

} //end of namespace wd
    
#endif
