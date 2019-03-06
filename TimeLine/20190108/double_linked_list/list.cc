/// @file    list.cc
/// @data    2019-01-09 22:22:39
 
#include "list.h"
#include <iostream>
 
using std::cout;
using std::endl;
 
List::List()
: _head(new Node())
, _tail(_head)
, _size(0)
{
    _head->next  =  _head->pre = NULL;
}

void List::push_back(int value) {
    _tail->next = new Node;
    _tail->next->pre = _tail;
    _tail = _tail->next;
    _tail->data = value;
    _tail->next = NULL;
    _size++;
}

void List::push_front(int value) {
    if (_size) {
        _head->next->pre = new Node;
        _head->next->pre->pre = _head;
        _head->next->pre->next = _head->next;
        _head->next = _head->next->pre;
        _head->next->data = value;
    }
    else {
        _tail = new Node;
        _tail->next = NULL;
        _head->next = _tail;
        _tail->pre = _head;
        _tail->data = value;
    }
    _size++;
}

void List::pop_back() {
    if (_size) {
        _tail = _tail->pre;
        delete _tail->next;
        _tail->next = NULL;
        _size--;
    }
    else {
        cout << "链表空" << endl;
    }
}

void List::pop_front() {
    if (_size == 0)
        cout << "链表空" << endl;
    else if (_size == 1) {
        delete _tail;
        _tail = _head;
        _size--;
    }
    else {
        _head->next = _head->next->next;
        delete _head->next->pre;
        _head->next->pre = _head;
        _size--;
    }
}

void List::insert(Node *n, int value) {
    n = n->pre;
    n->next->pre = new Node;
    n->next->pre->pre = n;
    n->next->pre->next = n->next;
    n->next = n->next->pre;
    n->next->data = value;
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
        while (p) {
            cout << p->data << endl;
            p = p->next;
        }
    }
    else
        cout << "链表空，不打印" << endl;
}

List::~List() {
    if (_size) {
        _head = _head->next;
        while (_head->pre)   //链表空，只剩头节点，这里会出错
            delete _head->pre;
        delete _head;
    }
    else
        delete _head;    //链表空时，单独释放
}
