/// @file    Thread.h
/// @author  moyin(moyin1004@163.com)
/// @data    2019-02-09 19:10:28
 
#ifndef __THREAD_H__
#define __THREAD_H__
    
#include "Noncopyable.h"
#include <pthread.h>

namespace wd {

class Thread 
: Noncopyable
{
public:
    Thread();

    virtual
    ~Thread();

    void start();
    void join();

    bool isRunning() const {  return _isRunning;  }

private:
    virtual
    void run()=0;

    static void *threadFunc(void *);

    pthread_t _pthid;
    bool _isRunning;
};

} //end of namespace wd

#endif
