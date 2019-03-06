// @file    stack.cc
/// @data    2019-01-08 23:20:33
 
#include "stack.h"
#include <iostream>
 
using std::cout;
using std::endl;

Stack::Stack()
: _top(-1)
{}

void Stack::push(int data){
    if (!full())
        _data[++_top] = data;
    else
        cout << "栈满" << endl;
}

void Stack::pop() {
    if (!empty())
        _top--;
    else
        cout << "栈空" << endl;
}

int Stack::top() {
    if (!empty())
        return _data[_top];
    else {
        cout << "栈空" << endl;
        return 0;
    }
}

bool Stack::empty() {
    if (_top == -1)
        return true;
    else
        return false;
}

bool Stack::full() {
    if (_top == 9)
        return true;
    else
        return false;
}
