/// @file    stack.h
/// @data    2019-01-08 23:13:11
 
#ifndef __STACK_H__
#define __STACK_H__

class Stack {
public:
    Stack();
    void push(int);
    void pop();
    int top();
    bool empty();
    bool full();
private:
    int _data[10];
    int _top;
};
    
#endif
