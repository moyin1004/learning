#include "stack.h"

// 顺序存储
void InitStack(SqStack &S) {
    S.top = -1;
}

void DestoryStack(SqStack &S) {
    S.top = -1;
}

bool Push(SqStack &S, ElemType x) {
    if (S.top == MaxSize-1) return false;
    S.data[++S.top] = x;
    return true;
}

bool Pop(SqStack &S, ElemType &x) {
    if (StackEmpty(S)) return false;
    x = S.data[S.top--];
    return true;
}

bool GetTop(SqStack &S, ElemType &x) {
    if (StackEmpty(S)) return false;
    x = S.data[S.top];
    return true;
}

bool StackEmpty(SqStack S) {
    if (S.top == -1) return true;
    return false;
}

// 链式存储
bool StackEmpty(LiStack S) {
    if (!S->top) return true;
    return false;
}

void InitStack(LiStack &S) {
    S = (LiStack)malloc(sizeof(LinkNode));
    S->top = NULL;
}

void DestoryStack(LiStack &S) {
    ElemType temp;
    while (!StackEmpty(S)) {
        Pop(S, temp);
    }
    free(S);
}

bool Push(LiStack &S, ElemType x) {
    LinkNode *p = (LinkNode*)malloc(sizeof(LinkNode));
    if (!p) return false;
    p->data = x;
    p->top = S->top;
    S->top = p;
    return true;
}

bool Pop(LiStack &S, ElemType &x) {
    if (StackEmpty(S)) return false;
    LinkNode *p = S->top;
    x = p->data;
    S->top = p->top;
    free(p);
    return true;
}

bool GetTop(LiStack &S, ElemType &x) {
    if (StackEmpty(S)) return false;
    x = S->top->data;
    return true;
}