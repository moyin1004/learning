/// @file    main.cc
/// @data    2019-01-10 13:34:32
 
#include "list.h"
#include <iostream>
 
using std::cout;
using std::endl;
 
void test1() {
    List l;
    l.push_front(2);
    cout << "打印链表" << endl;
    l.display();
    l.push_back(3);
    l.push_front(1);
    l.push_back(4);
    cout << "打印链表" << endl;
    l.display();

    l.pop_back();
    cout << "打印链表" << endl;
    l.display();

    l.pop_front();
    cout << "打印链表" << endl;
    l.display();

    l.pop_front();
    l.pop_back();
    cout << "打印链表" << endl;
    l.display();

    l.pop_front();
    l.pop_back();
}

int main() {
    test1();
    return 0;
}
