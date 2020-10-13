#include "search.h"
#include "util.h"

void Reverse(int A[], int l, int r) {
    int k = 1;
    for (int i = l; i < (r+l)/2; ++i) {
        swap(A[i], A[r-k]);
        ++k;
    }
}

int BinarySearch(int A[], int n, int x) {
    int l = 0;
    int r = n;
    int mid = 0;
    while (l < r) {
        mid = l + (r - l) / 2;
        if (x == A[mid]) break;
        else if (x > A[mid]) l = mid+1;
        else r = mid;
    }
    return A[mid] == x ? mid : -1;
}

int RecursionBinarySearch(int A[], int l, int r, int x) {
    if (l == r) return -1;
    int mid = l + (r-l)/2;
    if (A[mid] == x) return mid;
    else if (A[mid] < x) return RecursionBinarySearch(A, mid+1, r, x);
    else return RecursionBinarySearch(A, l, mid, x);
}

void SearchInsert(int A[], int n, int x) {
    int l = 0;
    int r = n;
    int mid = 0;
    while (l < r) {
        mid = l + (r - l) / 2;
        if (x == A[mid]) break;
        else if (x > A[mid]) l = mid+1;
        else r = mid;
    }
    if (A[mid] == x && mid < n-1) {
        swap(A[mid], A[mid+1]);
        Print(A, n);
    }
    if (l == r) {
        for (int i = n; i > l; --i) A[i] = A[i-1];
        A[l] = x;
        Print(A, n+1);
    }
}

int Search_Seq(SeqList S, ElemType x) {
    int i = 0;
    for (i = 0; i < S.length && S.data[i] != x; ++i);
    return i == S.length ? -1 : i;
}

#if 0
int Search_Seq(SeqList S, ElemType x) {
    S.data[0] = key; // 哨兵
    int i = 0;
    for (i = S.length; S.data[i] != x; --i);
    return i;
}
#endif