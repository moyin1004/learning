/// @file    EventLoop.h
/// @author  moyin(moyin1004@163.com)
/// @data    2019-02-20 17:30:23
 
#ifndef __EVENTLOOP_H__
#define __EVENTLOOP_H__

#include "MutexLock.h"
#include <sys/epoll.h>
#include <vector>
#include <map>
#include <memory>
#include <functional>

namespace wd {

class Acceptor;
class TcpConnection;
class EventLoop {
public:
    using TcpConnectionCallback =
        std::function<void(const std::shared_ptr<TcpConnection>)>;
    using Functor = std::function<void()>;

    EventLoop(Acceptor &acceptor);
    ~EventLoop();

    void loop();
    void unloop();
    void runInLoop(Functor &&cb);

    void doPendingFunctors();

    void setConnectionCallback(TcpConnectionCallback && cb)
    {   _onConnectionCallback = std::move(cb);  }

    void setMessageCallback(TcpConnectionCallback && cb)
    {   _onMessageCallback = std::move(cb); }

    void setCloseCallback(TcpConnectionCallback && cb)
    {   _onCloseCallback = std::move(cb);   }


private:
    int creatEpollFd();
    int creatEventFd();
    void addEpollReadFd(int fd);
    void delEpollReadFd(int fd);

    void waitEpollFds();

    void handleNewConnection();
    void handleMessage(int peerfd);
    void handleRead();
    void wakeup();

private:
    int _epollfd;
    int _eventfd;
    Acceptor &_acceptor;
    std::map<int, std::shared_ptr<TcpConnection>> _connections;
    std::vector<struct epoll_event> _eventList;
    bool _isLooping;

    MutexLock _mutex;
    std::vector<Functor> _pendingFunctors; //等待执行的函数，临界资源

    TcpConnectionCallback _onConnectionCallback;
    TcpConnectionCallback _onMessageCallback;
    TcpConnectionCallback _onCloseCallback;
};

} //end of namespace wd
    
#endif
