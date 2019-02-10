/// @file    list.h
/// @data    2019-01-09 22:13:29
 
#ifndef __LISH_H__
#define __LISH_H__
    
class Node {
public:
    int data;
    Node *pre;
    Node *next;
};

class List {
public:
    List();
    ~List();
    void push_back(int value);
    void push_front(int value);
    void pop_back();
    void pop_front();
    void insert(Node *, int value);
    void erase(Node *);
    void display() const;
private:
    Node *_head;
    Node *_tail;
    int _size;
};

#endif
