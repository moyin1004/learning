/// @file    queue.cc
/// @data    2019-01-09 17:50:24
 
#include "queue.h"
#include <iostream>
 
using std::cout;
using std::endl;

//Queue::Queue()
//: _front(0)
//, _rear(0)
//{}

void Queue::push(int data) {
    if (!full()) {
        _data[_rear] = data;
        _rear = (_rear + 1) % Maxsize;
    }
    else
        cout << "队列满" << endl;
}

void Queue::pop() {
    if (!empty())
        _front = (_front + 1) % Maxsize;
    else
        cout << "队列空" << endl;
}

int Queue::front() {
    if (!empty())
        return _data[_front];
    else {
        cout << "队列空" << endl;
        return 0;
    }
}

int Queue::back() {
    if (!empty())
        return _data[(_rear + Maxsize -1) % Maxsize];
    else {
        cout << "队列空" << endl;
        return 0;
    }
}

bool Queue::empty() {
    if (_front == _rear)
        return true;
    else
        return false;
}

bool Queue::full() {
    if (_front == (_rear + 1) % Maxsize)
        return true;
    else
        return false;
}
