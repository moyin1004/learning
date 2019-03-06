/// @file    Thread.cc
/// @author  moyin(moyin1004@163.com)
/// @data    2019-02-09 19:27:56
 
#include "Thread.h"
#include <pthread.h>
#include <iostream>
 
namespace wd {

Thread::Thread()
: _pthid(0)
, _isRunning(false)
{}

void Thread::start() {
    pthread_create(&_pthid, NULL, threadFunc, this);
    _isRunning = true;
}

void * Thread::threadFunc(void *arg) {
    Thread *p = static_cast<Thread *>(arg);
    if (p) p->run();

    return NULL;
}

void Thread::join() {
    if (_isRunning) {
        pthread_join(_pthid, NULL);
        _isRunning = false;
    }
}

Thread::~Thread() {
    if (_isRunning) {
        pthread_detach(_pthid);
        _isRunning = false;
    }
}

} //end of namespace wd
