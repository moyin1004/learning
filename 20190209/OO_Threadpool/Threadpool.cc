/// @file    Threadpool.cc
/// @author  moyin(moyin1004@163.com)
/// @data    2019-02-10 20:18:25
 
#include "Threadpool.h"
#include "WorkerThread.h"
#include <unistd.h>
#include <iostream>
 
using std::cout;
using std::endl;
using std::unique_ptr;

namespace wd {

Threadpool::Threadpool(size_t threadNum, size_t queSize)
: _threadNum(threadNum)
, _queSize(queSize)
, _threads()
, _taskque(_queSize)
, _isExit(false)
{
    _threads.reserve(_threadNum);
}

Threadpool::~Threadpool() {
    if (!_isExit)
        stop();
}

void Threadpool::start() {
    for (size_t i = 0; i != _threadNum; ++i) {
        unique_ptr<Thread> up(new WorkerThread(*this));
        _threads.push_back(std::move(up));
    }
    for (auto &threadPtr : _threads) threadPtr->start();
}

void Threadpool::addTask(Task *ptask) {
    _taskque.push(ptask);
}
            
Task * Threadpool::getTask() {
    return _taskque.pop();
}

void Threadpool::threadFunc() {
    while (!_isExit) {
        Task *ptask = getTask();
        if (ptask) ptask->process();
    }
}
void Threadpool::stop() {
    if (!_isExit) {
        while (!_taskque.empty()) {
            usleep(100);
        }
        _isExit = true;
        _taskque.wakeup();
        for (auto &threadPtr : _threads) {
            threadPtr->join();
        }
    }
}

} //end of namespce wd
