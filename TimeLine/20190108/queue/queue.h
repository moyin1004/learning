/// @file    queue.h
/// @data    2019-01-09 17:23:05
 
#include <iostream>

using std::cout;
using std::endl;

const int Maxsize = 10;

#ifndef __QUEUE_H__
#define __QUEUE_H__

class Queue {
public:
    void push(int);
    void pop();
    int front();
    int back();
    bool empty();
    bool full();
//    void get() {
//        cout << this->_front << endl;
//        cout << this->_rear << endl;
//    }
private:
    int _data[Maxsize];
    int _front = 0;
    int _rear = 0;
};

#endif
