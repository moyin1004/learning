#ifndef __SEARCH__
#define __SEARCH__

#include "type.h"
#include "liner_list.h"

void Reverse(int A[], int l, int r);
void SearchInsert(int A[], int n, int x);

int Search_Seq(SeqList S, ElemType x);

int BinarySearch(int A[], int n, int x);
int RecursionBinarySearch(int A[], int l, int r, int x);

// 分块
typedef struct {
    ElemType maxValue;
    int low, high;
} Index;
// ElemType List[100];

// B树
struct Node {
    ElemType keys[4];        //关键字
    struct Node *child[5];   //分叉
    int num;
};

#endif