/// @file    test.cc
/// @author  moyin(moyin1004@163.com)
/// @data    2019-02-09 21:54:34
 
#include "Task.h"
#include "Threadpool.h"
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <memory>
using namespace std;
using namespace wd;
 
class Mytask
: public Task
{
public:
    void process() {
        ::srand(::time(NULL));
        int number = rand() % 100;
        cout << "pthid " << pthread_self() << " : number = " << number <<  endl;
        sleep(1);
    }
};

void test() {
    cout << "main Thread " << pthread_self() << endl;
    unique_ptr<Task> up(new Mytask());
    unique_ptr<Threadpool> threadPoolPtr(new Threadpool(4, 10));
    threadPoolPtr->start();

    int cnt = 20;
    while(cnt--) threadPoolPtr->addTask(up.get());

    cout << "test(): exit while()" << endl;
    threadPoolPtr->stop();
}

int main() {
    test();

    return 0;
}
