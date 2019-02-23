/// @file    Condition.cc
/// @author  moyin(moyin1004@163.com)
/// @data    2019-02-09 20:44:21
 
#include "Condition.h"
#include "MutexLock.h"
#include <pthread.h>
#include <iostream>
 
using std::cout;
using std::endl;
using std::cerr;

namespace wd {

Condition::Condition(MutexLock &mutex)
: _mutex(mutex)
{
    if (pthread_cond_init(&_cond, NULL))
        cerr << "pthread_cond_init" << endl;
}

void Condition::wait() {
    if (pthread_cond_wait(&_cond, _mutex.getMutexLockPtr()))
        cerr << "pthread_cond_wait" << endl;
}

void Condition::notify() {
    if (pthread_cond_signal(&_cond))
        cerr << "pthread_cond_signal" << endl;
}

void Condition::notifyAll() {
    if (pthread_cond_broadcast(&_cond))
        cerr << "pthread_cond_broadcast" << endl;
}

Condition::~Condition() {
    if (pthread_cond_destroy(&_cond))
        cerr << "pthread_cond_destroy" << endl;
}

} //end of namespace wd
