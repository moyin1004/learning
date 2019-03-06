/// @file    Producer.h
/// @author  moyin(moyin1004@163.com)
/// @data    2019-02-09 21:37:56
 
#ifndef __PRODUCER_H__
#define __PRODUCER_H__
    
#include "Thread.h"
#include "TaskQueue.h"
#include <cstdlib>
#include <iostream>

namespace wd {

class Producer 
: public Thread
{
public:
    Producer(TaskQueue &tq)
    : _taskque(tq)
    {}

private:
    void run() override {
        ::srand(::clock());
        int cnt = 20;
        while (cnt--) {
            int number = ::rand() % 100;
            _taskque.push(number);
            std::cout << ">> Producer " << pthread_self() << ":"
                      << " producer a number = " << number << std::endl;
        }
    }

    TaskQueue &_taskque;
};

} //end of namespace wd

#endif
