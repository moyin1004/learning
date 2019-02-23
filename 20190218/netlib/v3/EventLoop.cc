/// @file    EventLoop.cc
/// @author  moyin(moyin1004@163.com)
/// @data    2019-02-20 17:40:37
 
#include "Mylogger.h"
#include "EventLoop.h"
#include "Acceptor.h"
#include "TcpConnection.h"
#include <unistd.h>
#include <sys/eventfd.h>
#include <iostream>
#include <memory>

using std::cout;
using std::endl;
using std::string;
using std::shared_ptr;
 
namespace wd {
EventLoop::EventLoop(Acceptor &acceptor)
: _epollfd(creatEpollFd())
, _eventfd(creatEventFd())
, _acceptor(acceptor)
, _eventList(1024)
, _isLooping(false)
{
    addEpollReadFd(_acceptor.fd());
    addEpollReadFd(_eventfd);
}

EventLoop::~EventLoop() {
    ::close(_epollfd);
}

void EventLoop::loop() {
    _isLooping = true;
    while (_isLooping) waitEpollFds();
}

void EventLoop::unloop() {
    if (_isLooping) _isLooping = false;
}

void EventLoop::runInLoop(Functor &&cb) {
    {
        MutexLockGuard autolock(_mutex);
        _pendingFunctors.push_back(std::move(cb));
    }
    wakeup(); //通知IO线程
}

int EventLoop::creatEpollFd() {
    int fd = ::epoll_create1(0);
    if (fd == -1) logError(">> epoll_create1");
    return fd;
}
 
int EventLoop::creatEventFd() {
    int fd = ::eventfd(0, 0);
    if (fd == -1) logError(">> eventfd");
    return fd;
}

void EventLoop::addEpollReadFd(int fd) {
    struct epoll_event value;
    value.events = EPOLLIN;
    value.data.fd = fd;
    value.events = EPOLLIN;
    int ret = ::epoll_ctl(_epollfd, EPOLL_CTL_ADD, fd, &value);
    if (ret == -1) logError(">> epoll_ctl");
}

void EventLoop::delEpollReadFd(int fd) {
    struct epoll_event value;
    value.events = EPOLLIN;
    value.data.fd = fd;
    value.events = EPOLLIN;
    int ret = ::epoll_ctl(_epollfd, EPOLL_CTL_DEL, fd, &value);
    if (ret == -1) logError(">> epoll_ctl");
}

void EventLoop::waitEpollFds() {
    int nready;
    do {
        nready = ::epoll_wait(_epollfd, &*_eventList.begin(), _eventList.size(), 5000);
    } while (nready == -1 && errno == EINTR);

    if (nready == 0) {
        cout << "epoll_wait timeout!" << endl;
    }
    else if (nready == -1) {
        logError(">> epoll_wait");
        return;
    }
    else {
        if (nready == static_cast<int>(_eventList.size())) {
            _eventList.resize(2 * _eventList.size());
        }

        for (int i = 0; i < nready; ++i) {
            if (_eventList[i].data.fd == _acceptor.fd() &&
                _eventList[i].events & EPOLLIN) {
                handleNewConnection();
            }
            else if (_eventList[i].data.fd == _eventfd) {
                handleRead();
                doPendingFunctors();
            }
            else handleMessage(_eventList[i].data.fd);
        }
    }
}

void EventLoop::handleNewConnection() {
    int peerfd = _acceptor.accept();
    addEpollReadFd(peerfd);

    shared_ptr<TcpConnection> connection(new TcpConnection(peerfd, *this));
    _connections.insert(std::make_pair(peerfd, connection));
    connection->setConnectionCallback(_onConnectionCallback);
    connection->setMessageCallback(_onMessageCallback);
    connection->setCloseCallback(_onCloseCallback);

    connection->handleConnectionCallback();
}

void EventLoop::handleMessage(int peerfd) {
    auto iter = _connections.find(peerfd);
    if (iter != _connections.end()) {
        auto connection = iter->second;
        bool closed = connection->isClosed();
        if (!closed) {
            connection->handleMessageCallback();
        }
        else { //连接断开的情况
            connection->handleCloseCallback();
            delEpollReadFd(peerfd);
            _connections.erase(peerfd);
        }
    }
}

void EventLoop::handleRead() {
    uint64_t num = 0;
    int ret = ::read(_eventfd, &num, sizeof(num)); //如果计算器值为0，这里阻塞
    if (ret != sizeof(num)) logError(">> read");
}

void EventLoop::wakeup() {
    uint64_t one = 1;
    int ret = ::write(_eventfd, &one, sizeof(one));
    if (ret != sizeof(one)) logError(">> write");
}

void EventLoop::doPendingFunctors() {
    std::vector<Functor> tmp;
    {
        MutexLockGuard autolock(_mutex);
        tmp.swap(_pendingFunctors); //交换之后_pendingFunctors被清空
    }
    for (auto funtor : tmp) funtor();
}

} //end of namespace wd
