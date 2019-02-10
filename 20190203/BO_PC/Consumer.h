/// @file    Consumer.h
/// @author  moyin(moyin1004@163.com)
/// @data    2019-02-09 21:45:19
 
#ifndef __CONSUMER_H__
#define __CONSUMER_H__

#include "TaskQueue.h"
#include <iostream>

namespace wd {

class Consumer {
public:
    void run(TaskQueue &taskque) {
        int cnt = 20;
        while (cnt--) {
            int number = taskque.pop();
            std::cout << ">> Consumer " << pthread_self() << ":"
                      << " consumer a number = " << number << std::endl << std::endl;
        }
    }
};

} //end of namespace wd

#endif
