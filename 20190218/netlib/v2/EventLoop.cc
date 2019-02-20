/// @file    EventLoop.cc
/// @author  moyin(moyin1004@163.com)
/// @data    2019-02-20 17:40:37
 
#include "Mylogger.h"
#include "EventLoop.h"
#include "Acceptor.h"
#include "TcpConnection.h"
#include <unistd.h>
#include <iostream>
#include <memory>

using std::cout;
using std::endl;
using std::string;
 
namespace wd {
EventLoop::EventLoop(Acceptor &acceptor)
: _eventfd(creatEpollFd())
, _acceptor(acceptor)
, _eventList(1024)
, _isLooping(false)
{
    addEpollReadFd(_acceptor.fd());    
}

EventLoop::~EventLoop() {
    ::close(_eventfd);
}

void EventLoop::loop() {
    _isLooping = true;
    while (_isLooping) waitEpollFds();
}

void EventLoop::unloop() {
    if (_isLooping) _isLooping = false;
}

int EventLoop::creatEpollFd() {
    int fd = ::epoll_create1(0);
    if (fd == -1) logError(">> epoll_create1");
    return fd;
}
    
void EventLoop::addEpollReadFd(int fd) {
    struct epoll_event value;
    value.events = EPOLLIN;
    value.data.fd = fd;
    value.events = EPOLLIN;
    int ret = ::epoll_ctl(_eventfd, EPOLL_CTL_ADD, fd, &value);
    if (ret == -1) logError(">> epoll_ctl");
}

void EventLoop::delEpollReadFd(int fd) {
    struct epoll_event value;
    value.events = EPOLLIN;
    value.data.fd = fd;
    value.events = EPOLLIN;
    int ret = ::epoll_ctl(_eventfd, EPOLL_CTL_DEL, fd, &value);
    if (ret == -1) logError(">> epoll_ctl");
}

void EventLoop::waitEpollFds() {
    int nready;
    do {
        nready = ::epoll_wait(_eventfd, &*_eventList.begin(), _eventList.size(), 5000);
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
            else handleMessage(_eventList[i].data.fd);
        }
    }
}

void EventLoop::handleNewConnection() {
    int peerfd = _acceptor.accept();
    addEpollReadFd(peerfd);
    std::shared_ptr<TcpConnection> connection(new TcpConnection(peerfd));
    cout << ">>" << connection->toString() << " has connected" << endl;

    _connections.insert(std::make_pair(peerfd, connection));
}

void EventLoop::handleMessage(int peerfd) {
    auto iter = _connections.find(peerfd);
    if (iter != _connections.end()) {
        auto connection = iter->second;
        bool closed = connection->isClosed();
        if (!closed) {
            string msg = connection->receive();
            cout << ">> server receive: " << msg << endl;
            connection->send(msg);
        }
        else {
            cout << ">>" << connection->toString() << " has closed!" << endl;
            delEpollReadFd(peerfd);
            _connections.erase(peerfd);
        }
    }
}

} //end of namespace wd
