/// @file    main.cc
/// @data    2019-01-09 18:13:49
 
#include "queue.h"
#include <iostream>
 
using std::cout;
using std::endl;

void test1() {
    Queue q;
    q.push(10);
    q.push(11);
    q.push(16);
    q.push(18);
    q.push(10);
    q.push(10);
    q.push(10);
    q.push(10);
    q.push(22);
    q.push(20);
    q.push(10);
    cout << "队头" << q.front() << endl;
    cout << "队尾" << q.back() << endl;
    q.pop();
    q.push(100);
    cout << "pop和push(100)后队头" << q.front() << endl;
    cout << "pop和push(100)后队尾" << q.back() << endl;
}

void test2() {
    Queue q;
    q.push(10);
    q.push(11);
    cout << "队头" <<  q.front() << endl;
    cout << "队尾" << q.back() << endl;
    q.pop();
    q.pop();
    q.pop();
}

void test3() {
    Queue q;
    q.push(10);
    q.push(11);
    q.push(16);
    q.push(18);
    cout << "队头" <<  q.front() << endl;
    cout << "队尾" << q.back() << endl;
}

int main() {
    cout << "test1:" << endl;
    test1();
    cout << endl;
    cout << "test2:" << endl;
    test2();
    cout << endl;
    cout << "test3:" << endl;
    test3();
    cout << endl;

    return 0;
}
