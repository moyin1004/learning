/// @file    Producer.h
/// @author  moyin(moyin1004@163.com)
/// @data    2019-02-09 21:37:56
 
#ifndef __PRODUCER_H__
#define __PRODUCER_H__
    
#include "TaskQueue.h"
#include <cstdlib>
#include <iostream>

namespace wd {

class Producer {
public:
    void run(TaskQueue &taskque) {
        ::srand(::clock());
        int cnt = 20;
        while (cnt--) {
            int number = ::rand() % 100;
            taskque.push(number);
            std::cout << ">> Producer " << pthread_self() << ":"
                      << " producer a number = " << number << std::endl;
        }
    }
};

} //end of namespace wd

#endif
