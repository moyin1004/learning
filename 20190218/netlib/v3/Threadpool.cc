/// @file    Threadpool.cc
/// @author  moyin(moyin1004@163.com)
/// @data    2019-02-10 20:18:25
 
#include "Thread.h"
#include "Threadpool.h"
#include <unistd.h>
#include <iostream>
#include <functional>
 
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
        unique_ptr<Thread> up(new Thread(
            std::bind(&Threadpool::threadFunc, this)            
        ));
        _threads.push_back(std::move(up));
    }
    for (auto &threadPtr : _threads) threadPtr->start();
}

void Threadpool::addTask(Task &&task) {
    _taskque.push(std::move(task));
}
            
Task Threadpool::getTask() {
    return _taskque.pop();
}

void Threadpool::threadFunc() {
    while (!_isExit) {
        Task task = getTask();
        if (task) task();
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
