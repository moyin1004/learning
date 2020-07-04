#include <iostream>
#include <cctype>
#include <algorithm>
#include <cassert>
#include "util.h"
#include "linked_list.h"
#include "stack.h"
#include "queue.h"
#include "search.h"
#include "algorithm.h"
#include "tree.h"
using namespace std;

void test_linked_list() {
    LinkList L;
    // InitList(L);
    L = List_TailInsert(L);
    PrintList(L);
    bool ret = ListInsert(L, 2, 10);
    cout << ret << endl;
    cout << ListInsert(L, 7, 4) << endl;
    PrintList(L);
    int data = 0;
    ListDelete(L, 3, data);
    PrintList(L);
    cout << GetElem(L, 3)->data << endl;
    Reverse(L);
    PrintList(L);
    DestoryList(L);
}

void test_stack() {
    cout << "---------stack-----------" << endl;
    Stack S;
    InitStack(S);
    Push(S, 1);
    Push(S, 2);
    Push(S, 3);
    Push(S, 4);
    ElemType data = 0;
    GetTop(S, data);
    cout << data << endl;
    Pop(S, data);
    Pop(S, data);
    Pop(S, data);
    cout << data << endl;
    Pop(S, data);
    cout << Pop(S, data) << endl;
    DestoryStack(S);
    cout << "---------stack end-----------" << endl;
}

void test_queue() {
    cout << "---------queue-----------" << endl;
    Queue Q;
    InitQueue(Q);
    cout << "is empty: " << QueueEmpty(Q) << endl;
    EnQueue(Q, 1);
    EnQueue(Q, 2);
    EnQueue(Q, 3);
    EnQueue(Q, 4);
    cout << "is insert: " << EnQueue(Q, 5) << endl;
    ElemType data = 0;
    DeQueue(Q, data);
    DeQueue(Q, data);
    GetHead(Q, data);
    cout << data << endl;
    EnQueue(Q, 10);
    EnQueue(Q, 11);
    cout << "is insert: " << EnQueue(Q, 12) << endl;
    DeQueue(Q, data);
    DeQueue(Q, data);
    DeQueue(Q, data);
    DeQueue(Q, data);
    cout << data << endl;
    cout << "is empty: " << QueueEmpty(Q) << endl;
    cout << GetHead(Q, data) << endl;
    DestoryQueue(Q);
    cout << "---------queue end-----------" << endl;
}

void test_search_insert() {
    int A[20] = {2, 4, 5, 6, 8, 11, 11, 13, 14, 15};
    SearchInsert(A, 10, 16);
    SearchInsert(A, 11, 9);
    SearchInsert(A, 12, 1);
    SearchInsert(A, 13, 14);
    Reverse(A, 0, 9);
    Reverse(A, 9, 13);
    Reverse(A, 0, 13);
    Print(A, 13);
}

void test_find_majority() {
    int a[] = {0, 5, 5, 3, 5, 7, 5, 5};
    int b[] = {0, 5, 5, 3, 5, 1, 5, 7};
    cout << FindMajority(a, 8) << endl;
    cout << FindMajority(b, 8) << endl;
}

void test_find_mid() {
    int a[] = {3, 4, 7, 9, 10};
    int b[] = {1, 5, 6, 8, 9};
    cout << FindMid(a, b, 5) << endl;
}

void test_avl_tree() {
    AVLTree T = NULL;
    T = Insert(T, 5);
    T = Insert(T, 4);
    T = Insert(T, 3);
    InOrder(T);
    PreOrder(T);
    T = Insert(T, 20);
    T = Insert(T, 11);
    cout << endl;
    InOrder(T);
    PreOrder(T);
    DestoryAVL(T);
}

int main() {
    // test_linked_list();
    // test_stack();
    // test_queue();
    // cout << bracket_matching() << endl;
    // cout << nifix2postfix() << endl;
    // cout << nifix2prefix() << endl;
    // cout << postfix_cul(nifix2postfix()) << endl;
    // test_search_insert();
    // test_find_majority();
    // test_find_mid();
    test_avl_tree();
    return 0;
}