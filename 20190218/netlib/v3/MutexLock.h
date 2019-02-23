/// @file    MutexLock.h
/// @author  moyin(moyin1004@163.com)
/// @data    2019-02-09 19:39:41
 
#ifndef __MUTEXLOCK_H__
#define __MUTEXLOCK_H__
  
#include "Noncopyable.h"
#include <pthread.h>

namespace wd {

class MutexLock
: Noncopyable
{
public:
    MutexLock();
    ~MutexLock();
    void lock();
    void unlock();

    pthread_mutex_t *getMutexLockPtr() {  return &_mutex;  }

private:
    pthread_mutex_t _mutex;
};

class MutexLockGuard {
public:
    MutexLockGuard(MutexLock &mutex)
    : _mutex(mutex)
    {  _mutex.lock();  }

    ~MutexLockGuard() {
        _mutex.unlock();
    }

private:
    MutexLock &_mutex;
};

} //end of namespace wd

#endif
