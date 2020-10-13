#ifndef __LINER_LIST__
#define __LINER_LIST__

#include "type.h"

/**
 * 顺序表
 */
// 静态分配
typedef struct {
    ElemType data[MaxSize];
    int length;
} SqList;

// 动态分配
typedef struct {
    ElemType *data;
    int max_size, length;                                       
} SeqList;

#ifdef STATIC_SEQUENCE                                                                                                      
    typedef SqList List;
#elif defined DYNAMIC_SEQUENCE
    typedef SeqList List;
#endif

void InitList(List &L);
void DestoryList(List &L);

bool ListInsert(List &L, int i, ElemType e);
bool ListDelete(List &L, int i, ElemType e);
int LocateElem(List &L, ElemType e);
ElemType GetElem(List &L, int i);

int Length(List &L);
void PrintList(List &L);
void Empty(List &L);

/**
 * 链表
 */
// 单链表
typedef struct LNode {
    ElemType data;
    struct LNode *next;
} LNode, *LinkList;

void InitList(LinkList &L);
void DestoryList(LinkList &L);
LinkList List_HeadInsert(LinkList &L);
LinkList List_TailInsert(LinkList &L);

bool ListInsert(LinkList &L, int i, ElemType e);
bool InsertPriorNode(LNode *p, ElemType e);
bool InsertNextNode(LNode *p, ElemType e);
bool ListDelete(LinkList &L, int i, ElemType e);
LNode *LocateElem(LinkList &L, ElemType e);
LNode *GetElem(LinkList &L, int i);

int Length(LinkList &L);
void PrintList(LinkList &L);
bool Empty(LinkList &L);

void Reverse(LinkList &L);

// 双链表
typedef struct DNode {
    ElemType data;
    struct DNode *prior, *next;
    int freq;
} DNode, *DLinkList;

bool InitList(DLinkList &L);
void DestoryList(DLinkList &L);
DLinkList List_HeadInsert(DLinkList &L);
DLinkList List_TailInsert(DLinkList &L);

bool ListInsert(DLinkList &L, int i, ElemType e);
bool InsertPriorNode(DNode *p, ElemType e);
bool InsertNextNode(DNode *p, ElemType e);
bool ListDelete(DLinkList &L, int i, ElemType e);
DNode *LocateElem(DLinkList &L, ElemType e);
DNode *GetElem(DLinkList &L, int i);

int Length(DLinkList &L);
void PrintList(DLinkList &L);
bool Empty(DLinkList &L);

void Reverse(DLinkList &L);

// 静态链表
typedef struct {
    ElemType data;
    int next;
} SLinkList[MaxSize];

#endif