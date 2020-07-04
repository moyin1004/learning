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