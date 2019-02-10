/// @file    TaskQueue.cc
/// @author  moyin(moyin1004@163.com)
/// @data    2019-02-09 21:27:49
 
#include "TaskQueue.h"
#include <iostream>
#include <unistd.h> 

using std::cout;
using std::endl;

namespace wd {

TaskQueue::TaskQueue(size_t size)
: _queSize(size)
, _que()
, _mutex()
, _notFull(_mutex)
, _notEmpty(_mutex)
{}

bool TaskQueue::full() const {
    return _que.size() == _queSize;
}

bool TaskQueue::empty() const {
    return _que.empty();
}

void TaskQueue::push(int number) {
    _mutex.lock();
    while (full()) {
        _notFull.wait();
    }

    _que.push(number);
    sleep(1);
    _notEmpty.notify();
    _mutex.unlock();
}

int TaskQueue::pop() {
    _mutex.lock();
    while (empty()) {
        _notEmpty.wait();
    }
    int ret = _que.front();
    _que.pop();
    _notFull.notify();
    _mutex.unlock();

    return ret;
}

} //end of namespace wd
