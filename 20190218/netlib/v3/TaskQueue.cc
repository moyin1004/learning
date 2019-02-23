/// @file    TaskQueue.cc
/// @author  moyin(moyin1004@163.com)
/// @data    2019-02-09 21:27:49
 
#include "TaskQueue.h"
#include <iostream>

using std::cout;
using std::endl;

namespace wd {

TaskQueue::TaskQueue(size_t size)
: _queSize(size)
, _que()
, _mutex()
, _notFull(_mutex)
, _notEmpty(_mutex)
, _used(true)
{}

bool TaskQueue::full() const {
    return _que.size() == _queSize;
}

bool TaskQueue::empty() const {
    return _que.empty();
}

void TaskQueue::push(const TaskType &t) {
    _mutex.lock();
    while (full()) {
        _notFull.wait();
    }

    _que.push(t);
    _notEmpty.notify();
    _mutex.unlock();
}

TaskType TaskQueue::pop() {
    _mutex.lock();
    while (_used && empty()) {
        _notEmpty.wait();
    }
    TaskType ret = _que.front();
    _que.pop();
    _notFull.notify();
    _mutex.unlock();

    return ret;
}

void TaskQueue::wakeup() {
    if (_used) _used = false;
    _notEmpty.notifyAll();
}

} //end of namespace wd
