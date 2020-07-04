#include "queue.h"

// 顺序存储
void InitQueue(SqQueue &Q) {
    Q.front = Q.rear = 0;
}

void DestoryQueue(SqQueue &Q) {
    Q.front = Q.rear = 0;
}

bool EnQueue(SqQueue &Q, ElemType x) {
    if ((Q.rear + 1) % MaxSize == Q.front) return false;
    Q.data[Q.rear] = x;
    Q.rear = (Q.rear + 1) % MaxSize;
    return true;
}

bool DeQueue(SqQueue &Q, ElemType &x) {
    if (QueueEmpty(Q)) return false;
    x = Q.data[Q.front];
    Q.front = (Q.front + 1) % MaxSize;
    return true;
}

bool GetHead(SqQueue &Q, ElemType &x) {
    if (QueueEmpty(Q)) return false;
    x = Q.data[Q.front];
    return true;
}

bool QueueEmpty(SqQueue Q) {
    return (Q.front == Q.rear);
}

// 链式存储
void InitQueue(LiQueue &Q) {
    Q.front = Q.rear = (QNode*)malloc(sizeof(QNode));
    Q.front->next = NULL;
}

void DestoryQueue(LiQueue &Q) {
    ElemType temp;
    while (!QueueEmpty(Q)) {
        DeQueue(Q, temp);
    }
    free(Q.front);
    Q.front = Q.rear = NULL;
}

bool EnQueue(LiQueue &Q, ElemType x) {
    QNode *s = (QNode*)malloc(sizeof(QNode));
    if (!s) return false;
    s->data = x;
    s->next = NULL;
    Q.rear->next = s;
    Q.rear = s;
    return true;
    /*
    QNode *s = (QNode*)malloc(sizeof(QNode));
    if (!s) return false;
    s->data = x;
    s->next = NULL;
    if (Q.front == NULL) { // 第一元素的处理
        Q.front = Q.front = s;
    }
    else {
        Q.rear->next = s;
        Q.rear = s;
    }
    return true;
    */
}

bool DeQueue(LiQueue &Q, ElemType &x) {
    if (QueueEmpty(Q)) return false;
    QNode *p = Q.front->next;
    if (Q.rear == p) Q.rear = Q.front;
    Q.front->next = p->next;
    x = p->data;
    free(p);
    return true;
    /*
    if (QueueEmpty(Q)) return false;
    QNode *p = Q.front;
    Q.front = p->next;
    x = p->data;
    if (Q.rear == p) Q.rear = Q.front = NULL;
    free(p);
    return true;
    */
}

bool GetHead(LiQueue &Q, ElemType &x) {
    if (QueueEmpty(Q)) return false;
    x = Q.front->next->data;
    return true;
}

bool QueueEmpty(LiQueue Q) {
    return (Q.front == Q.rear);
}