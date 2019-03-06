/// @file    list_new.cc
/// @data    2019-01-09 22:22:39
 
#include "list.h"     //修改版
#include <iostream>
 
using std::cout;
using std::endl;
 
List::List()
: _head(new Node())
, _tail(_head)
, _size(0)
{
    _head->next = _head->pre = _head;
}

void List::push_back(int value) {
    insert(_head, value);
    _tail = _head->pre;
}

void List::push_front(int value) {
    insert(_head->next, value);
}

void List::pop_back() {
    if (_size) {
        erase(_tail);
        _tail = _head->pre;
    }
    else
        cout << "链表空" << endl;
}

void List::pop_front() {
    if (_size)
        erase(_head->next);
    else
        cout << "链表空" << endl;
}

void List::insert(Node *n, int value) {
    Node *p = new Node();
    p->data = value;
    p->next = n;
    p->pre = n->pre;
    p->pre->next = p;
    n->pre = p;
    _size++;
}

void List::erase(Node *n) {
    n->next->pre = n->pre;
    n->pre->next = n->next;
    _size--;
    delete n;
}

void List::display() const {
    if (_size) {
        Node *p = _head->next;
        while (p != _head) {
            cout << p->data << endl;
            p = p->next;
        }
    }
    else
        cout << "链表空，不打印" << endl;
}

List::~List() {
    _head = _head->next;
    while (_head != _tail) {
        delete _head->pre;
        _head = _head->next;
    }
    delete _head;
}
