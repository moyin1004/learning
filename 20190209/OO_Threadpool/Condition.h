/// @file    Condition.h
/// @author  moyin(moyin1004@163.com)
/// @data    2019-02-09 20:39:19
 
#ifndef __CONDITION_H__
#define __CONDITION_H__
  
#include "Noncopyable.h"
#include <pthread.h>

namespace wd {

class MutexLock;

class Condition
: Noncopyable
{
public:
    Condition(MutexLock &mutex);
    ~Condition();

    void wait();
    void notify();
    void notifyAll();

private:
    MutexLock &_mutex;
    pthread_cond_t _cond;
};

} //end of namespace wd

#endif
