/// @file    WorkerThread.h
/// @author  moyin(moyin1004@163.com)
/// @data    2019-02-10 20:29:25
 
#ifndef __WORKERTHREAD_H__
#define __WORKERTHREAD_H__
    
#include "Thread.h"

namespace wd {

class Threadpool;
class WorkerThread
: public Thread
{
public:
    WorkerThread(Threadpool &threadpool);
private:
    void run() override;
    Threadpool &_threadpool;
};

} //end of namespace wd

#endif
