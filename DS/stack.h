#ifndef __STACK__
#define __STACK__

#include "type.h"

typedef struct {
    ElemType data[MaxSize];
    int top;
} SqStack;

typedef struct LinkNode{
    ElemType data;
    struct LinkNode *top;
} LinkNode, *LiStack;

#ifdef LINKED
    typedef LiStack Stack;
#else
    typedef SqStack Stack;
#endif

void InitStack(SqStack &S);
void DestoryStack(SqStack &S);
bool Push(SqStack &S, ElemType x);
bool Pop(SqStack &S, ElemType &x);
bool GetTop(SqStack &S, ElemType &x);
bool StackEmpty(SqStack S);

void InitStack(LiStack &S);
void DestoryStack(LiStack &S);
bool Push(LiStack &S, ElemType x);
bool Pop(LiStack &S, ElemType &x);
bool GetTop(LiStack &S, ElemType &x);
bool StackEmpty(LiStack S);

#endif