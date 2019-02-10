/// @file    test.cc
/// @author  moyin(moyin1004@163.com)
/// @data    2019-02-09 21:54:34
 
#include "Thread.h"
#include "Producer.h"
#include "Consumer.h"
#include "TaskQueue.h"
#include <unistd.h>
#include <iostream>
#include <memory>
using namespace std;
using namespace wd;
 
void test() {
    cout << "main Thread " << pthread_self() << endl;
    TaskQueue taskque(10);
    unique_ptr<Thread> producer(new Producer(taskque));
    unique_ptr<Thread> consumer(new Consumer(taskque));

    producer->start();
    consumer->start();
    producer->join();
    consumer->join();
}

int main() {
    test();

    return 0;
}
