#include "liner_list.h"
#include <cstdlib>
#include <iostream>
using namespace std;

static void IncreaseList(SeqList &L, int len) {
    L.data = (ElemType*)realloc(L.data, (L.length+len)*sizeof(ElemType));
    L.max_size += len;
}

void InitList(SqList &L) {
    L.length = 0;
}
void DestoryList(SqList &L) {
    L.length = 0;
}

void InitList(SeqList &L) {
    L.data = (ElemType*)malloc(MaxSize*sizeof(ElemType));
    L.length = 0;
    L.max_size = MaxSize;
}

void DestoryList(SeqList &L) {
    L.length = 0;
    if (L.data) {
        free(L.data);
        L.data = NULL;
    }
}

bool ListInsert(List &L, int i, ElemType e) {
    if (i < 1 || i > L.length || L.length >= MaxSize)
        return false;
    for (int j = L.length-1; j >= i; --j) {
        L.data[j] = L.data[j-1];
    }
    L.data[i-1] = e;
    ++L.length;
    return true;
}

bool ListDelete(List &L, int i, ElemType &e) {
    if (i < 1 || i > L.length)
        return false;
    e = L.data[i];
    for (int j = i; j < L.length; ++j) {
        L.data[j-1] = L.data[j];
    }
    --L.length;
    return true;
}

int LocateElem(List &L, ElemType e) {
    for (int i = 0; i < L.length; ++i) {
        if (e == L.data[i]) return i+1;
    }
    return 0;
}

ElemType GetElem(List &L, int i) {
    ElemType temp;
    if (i < 1 || i > L.length)
        return temp;
    return L.data[i-1];
}

int Length(List &L) {
    return L.length;
}

void PrintList(List &L) {
    for (int i = 0; i < L.length; ++i) {
        cout << L.data[i] << " ";
    }
    cout << endl;
}

void Empty(List &L) {
    L.length = 0;
}

/**
 * 链表操作实现
 */
void InitList(LinkList &L) {
    L = (LNode*)malloc(sizeof(LNode));
    L->next = NULL;
}

void DestoryList(LinkList &L) {
    LNode *p = L;
    LNode *q = L->next;
    cout << "detory: ";
    while (q) {
        cout << q->data << " ";
        free(p);
        p = q;
        q = q->next;
    }
    cout << endl;
    free(p);
    L = NULL;
}

LNode *GetElem(LinkList &L, int i) {
    if (i < 1) return NULL;
    LNode *p = L;
    int j = 0;
    while (p && j < i) {
        p = p->next;
        ++j;
    }
    return p;
}

bool InsertNextNode(LNode *p, ElemType e) {
    if (!p) return false;
    LNode *s = (LNode*)malloc(sizeof(LNode));
    if (!s) return false;
    s->data = e;
    s->next = p->next;
    p->next = s;
    return true;
}

LinkList List_TailInsert(LinkList &L) {
    int x;
    L = (LinkList)malloc(sizeof(LNode));
    L->next = NULL;
    LNode *s, *r = L;
    while (cin >> x) {
        s = (LNode*)malloc(sizeof(LNode)); 
        s->data = x;
        r->next = s;
        s->next = NULL;
        r = s;
    }
    return L;
}

LinkList List_HeadInsert(LinkList &L) {
    int x;
    L = (LinkList)malloc(sizeof(LNode));
    L->next = NULL;
    LNode *s, *r = L;
    while (cin >> x) {
        InsertNextNode(L, x);
    }
    return L;
}

bool InsertPriorNode(LNode *p, ElemType e) {
    if (!p) return false;
    LNode *s = (LNode*)malloc(sizeof(LNode));
    if (!s) return false;
    s->data = p->data;
    p->data = e;
    s->next = p->next;
    p->next = s;
    return true;
}

bool ListInsert(LinkList &L, int i, ElemType e) {
    LNode *p = GetElem(L, i-1);
    InsertNextNode(p, e);
    return true;
}

bool ListDelete(LinkList &L, int i, ElemType e) {
    LNode *p = GetElem(L, i-1);
    if (!p) return false;
    LNode *cnt = p->next;
    p->next = cnt->next;
    free(cnt);
    return true;
}

LNode *LocateElem(LinkList &L, ElemType e) {
    LNode *p = L->next;
    while (p) {
        if (p->data == e) return p;
        p = p->next;
    }
    return NULL;
}

int Length(LinkList &L) {
    LNode *p = L->next;
    int count = 0;
    while (p) {
        ++count;
        p = p->next;
    }
    return count;
}

void PrintList(LinkList &L) {
    LNode *p = L->next;
    while(p) {
        cout << p->data << " ";
        p = p->next;
    }
    cout << endl;
}

bool Empty(LinkList &L) {
    return (L->next == NULL);
}

void Reverse(LinkList &L) {
    // 头插法逆转
    // LNode *p = L->next;
    // while (p && p->next) {
    //     LNode *cnt = p->next;
    //     p->next = cnt->next;
    //     cnt->next = L->next;
    //     L->next = cnt;
    // }
    // 指向逆转
    LNode *new_head, *old_head, *temp;
    new_head = NULL;
    old_head = L->next;
    while (old_head) {
        temp = old_head->next;
        old_head->next = new_head;
        new_head = old_head;
        old_head = temp;
    }
    L->next = new_head;
}

// 双链表操作
bool InitList(DLinkList &L) {
    L = (DNode*)malloc(sizeof(DNode));
    if (!L) return false;
    L->next = L->prior = NULL;
    return true;
}

bool DeleteNextDNode(DNode *p) {
    if (!p || !p->next) return false;
    DNode *q = p->next;
    p->next = q->next;
    if (q->next)
        q->next->prior = p;
    free(q);
    return true;
}

void DestoryList(DLinkList &L) {
    while (L->next)
        DeleteNextDNode(L);
    free(L);
    L = NULL;
}
DLinkList List_HeadInsert(DLinkList &L);
DLinkList List_TailInsert(DLinkList &L);

bool ListInsert(DLinkList &L, int i, ElemType e);
bool InsertPriorNode(DNode *p, ElemType e);

bool InsertNextNode(DNode *p, ElemType e) {
    if (!p) return false;
    DNode *s = (DNode*)malloc(sizeof(DNode));
    if (!s) return false;
    s->data = e;
    s->prior = p;
    s->next = p->next;
    p->next = s;
    if (s->next)
        s->next->prior = s;
    return true;
}

bool ListDelete(DLinkList &L, int i, ElemType e);
DNode *LocateElem(DLinkList &L, ElemType e);
DNode *GetElem(DLinkList &L, int i);

int Length(DLinkList &L);
void PrintList(DLinkList &L);
bool Empty(DLinkList &L) {
    return (L->next == NULL);
}

void Reverse(DLinkList &L);

// 循环链表