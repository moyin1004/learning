#ifndef __QUEUE__
#define __QUEUE__

#include "type.h"

typedef struct {
    ElemType data[MaxSize];
    int front, rear;
} SqQueue;

typedef struct QNode {
    ElemType data;
    struct QNode *next;
} QNode;

typedef struct {
    struct QNode *front, *rear;
} LiQueue;

#ifdef LINKED
    typedef LiQueue Queue;
#else
    typedef SqQueue Queue;
#endif

void InitQueue(SqQueue &S);
void DestoryQueue(SqQueue &S);
bool EnQueue(SqQueue &S, ElemType x);
bool DeQueue(SqQueue &S, ElemType &x);
bool GetHead(SqQueue &S, ElemType &x);
bool QueueEmpty(SqQueue S);

void InitQueue(LiQueue &S);
void DestoryQueue(LiQueue &S);
bool EnQueue(LiQueue &S, ElemType x);
bool DeQueue(LiQueue &S, ElemType &x);
bool GetHead(LiQueue &S, ElemType &x);
bool QueueEmpty(LiQueue S);

#endif