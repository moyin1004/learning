/// @file    Consumer.h
/// @author  moyin(moyin1004@163.com)
/// @data    2019-02-09 21:45:19
 
#ifndef __CONSUMER_H__
#define __CONSUMER_H__

#include "Thread.h"
#include "TaskQueue.h"
#include <iostream>

namespace wd {

class Consumer 
: public Thread
{
public:
    Consumer(TaskQueue &tq)
    : _taskque(tq)
    , _m()
    {}    

private:
    void run() {
        int cnt = 20;
        while (cnt--) {
            int number = _taskque.pop();
            std::cout << ">> Consumer " << pthread_self() << ":"
                      << " consumer a number = " << number << std::endl << std::endl;
        }
    }

    TaskQueue &_taskque;
    MutexLock _m;
};

} //end of namespace wd

#endif
