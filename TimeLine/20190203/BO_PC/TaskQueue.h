/// @file    TaskQueue.h
/// @author  moyin(moyin1004@163.com)
/// @data    2019-02-09 21:23:05
 
#ifndef __TASKQUEUE_H__
#define __TASKQUEUE_H__
    
#include "Condition.h"
#include "MutexLock.h"
#include <queue>

namespace wd {

class TaskQueue {
public:
    TaskQueue(size_t size);

    bool full() const;
    bool empty() const;
    void push(int number);
    int pop();

private:
    size_t _queSize;
    std::queue<int> _que;
    MutexLock _mutex;
    Condition _notFull;
    Condition _notEmpty;
};

} //end of namespace wd

#endif
