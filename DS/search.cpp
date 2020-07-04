#include "search.h"
#include "util.h"

void Reverse(int A[], int l, int r) {
    int k = 1;
    for (int i = l; i < (r+l)/2; ++i) {
        swap(A[i], A[r-k]);
        ++k;
    }
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