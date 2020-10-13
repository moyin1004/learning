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
#include "sort.h"
#include "graph.h"
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
    PrintFunction(__FUNCTION__);
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
    PrintFunction(__FUNCTION__);
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
    PostOrder(T);
    DestoryTree(T);
}

void test_CreatBTreeByOrder() {
    PrintFunction(__FUNCTION__);
    int a[] = {4, 3, 10, 7, 8, 11, 5, 21, 10};
    int b[] = {7, 10, 8, 3, 4, 5, 21, 11, 10};
    BiTree T = CreatBTreeByOrder(a, b, 9);
    PreOrder(T);
    InOrder(T);
    PostOrder(T);

    DeleteXTree(T, 10);
    PreOrder(T);
    InOrder(T);
    PostOrder(T);

    DestoryTree(T);
    cout << "====================================" << endl;
}

void test_Sort() {
    PrintFunction(__FUNCTION__);
    int num = 11;
    int a[] = {7, 10, 8, 4, 3, 4, 5, 21, 11, 11, 20};
    int b[10];
    cout << "============InsertSort==========" << endl;
    Copy(a, b, num);
    InsertSort(b, num);
    Print(b, num);
    cout << "============ShellSort==========" << endl;
    Copy(a, b, num);
    ShellSort(b, num);
    Print(b, num);
    cout << "============BubbleSort==========" << endl;
    Copy(a, b, num);
    BubbleSort(b, num);
    Print(b, num);
    cout << "============QuickSort==========" << endl;
    Copy(a, b, num);
    QuickSort(b, 0, num-1);
    Print(b, num);
    cout << "============SelectSort==========" << endl;
    Copy(a, b, num);
    SelectSort(b, num);
    Print(b, num);
    cout << "============HeapSort==========" << endl;
    Copy(a, b, num);
    HeapSort(b, num);
    Print(b, num);
    cout << "============MergeSort==========" << endl;
    Copy(a, b, num);
    MergeSort(b, 0, num);
    Print(b, num);
    cout << "=============================================" << endl;
}

void test_Graph() {
    PrintFunction(__FUNCTION__);
    Graph G = BuildGraph();
    BFS(G, 0);
    cout << endl;
    DFSTraverse(G);
    cout << endl;
    Dijkstra(G, 0);
    cout << endl;
    DestoryGraph(G);
}

void test_Move() {
    PrintFunction(__FUNCTION__);
    int A[] = {4, 5, 6, 10, 9, 20, 21, 23, 25};
    int len = sizeof(A) / sizeof(int);
    Move(A, len);
    Print(A, len);
}


void test_Flag_Arrange() {
    PrintFunction(__FUNCTION__);
    int A[] = {1, 2, 3, 2, 3, 1, 2, 3, 1, 2, 1, 2};
    int len = sizeof(A) / sizeof(int);
    Flag_Arrange(A, len);
    Print(A, len);
}

void test_IsMinHeap() {
    PrintFunction(__FUNCTION__);
    int A[20];
    int n = 0;
    while (cin >> n) {
        for (int i = 0; i < n; ++i) cin >> A[i];
        cout << IsMinHeap(A, n) << endl;
    }
}

void test_ListSelectSort() {
    PrintFunction(__FUNCTION__);
    LinkList L;
    InitList(L);
    List_TailInsert(L);
    ListSelectSort(L);
    PrintList(L);
    DestoryList(L);
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
    // test_avl_tree();
    // test_CreatBTreeByOrder();
    // test_Sort();
    // test_Graph();
    // test_Move();
    // test_Flag_Arrange();
    // test_IsMinHeap();
    test_ListSelectSort();
    return 0;
}