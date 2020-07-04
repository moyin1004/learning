#ifndef __LINER_LIST__
#define __LINER_LIST__

#include "type.h"

typedef struct {
    ElemType data[MaxSize];
    int length;
} SqList;

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

#endif