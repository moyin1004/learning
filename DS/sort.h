#ifndef __SORT__
#define __SORT__
#include "type.h"

void InsertSort(int A[], int n);
void ShellSort(int A[], int n);

void BubbleSort(int A[], int n);
void QuickSort(int A[], int low, int high);

void SelectSort(int A[], int n);
void HeapInsert(ElemType A[], int n, ElemType x);
void HeapDelete(ElemType A[], int n, int i);
void HeapSort(ElemType A[], int N);

void MergeSort(ElemType A[], int l, int r);


// typedef struct LinkNode {
//     ElemType data;
//     struct LinkNode *next;
// } LinkNode, *LinkList;
// typedef struct {
//     LinkNode *front, *rear;
// } LinkQueue;

#endif