#include <iostream>
#include <bits/stdc++.h>
#include <cstdlib>
#include <ctime>

using namespace std;

void bubbleSort(int A[], int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 1; j < n - i; ++j) {
            if (A[j] < A[j-1]) {
                swap(A[j], A[j-1]);
            }
        }
    }
}
void insertSort(int A[], int n) {
    for (int i = 1; i < n; ++i) {
        for (int j = i; j > 0; --j) {
            if (A[j] < A[j-1]) {
                swap(A[j], A[j-1]);
            }
            else {
                break;
            }
        }
    }
}
void selectSort(int A[], int n) {
    int min = 0;
    for (int k = 0; k < n; ++k) {
        min = k;
        for (int i = k + 1; i < n; ++i) {
            if (A[i] < A[min]) {
                min = i;
            }
        }
        swap(A[min], A[k]);
    }
}

void merge(int A[], int lo, int mi, int hi) {
    int temp[hi-lo+1];
    int pos = 0;
    int i = lo, j = mi;
    while (i < mi && j < hi) {
        if (A[i] > A[j]) {
            temp[pos++] = A[j++];
        }
        else {
            temp[pos++] = A[i++];
        }
    }
    while (i < mi) {
        temp[pos++] = A[i++];
    }
    while (j < hi) {
        temp[pos++] = A[j++];
    }
    for (int k = 0; k < pos; ++k) {
        A[lo+k] = temp[k];
    }
}
void mergeSort(int A[], int lo, int hi) {
    if (hi - lo <= 1) {
        return ;
    }
    int mi = lo + (hi - lo) / 2;
    mergeSort(A, lo, mi);
    mergeSort(A, mi, hi);
    merge(A, lo, mi, hi);
}

void print(int A[], int n) {
    for (int i = 0; i < n; ++i) {
        printf("%d", A[i]);
        if (i != n-1) {
            printf(" ");
        }
    }
    printf("\n");
}

void qSort(int A[], int l, int r) {
    if (l >= r) return ;
    srand(time(NULL)); // use current time as seed for random generator
    int bound = A[rand() % (r-l+1) + l];
    int i = l, j = r;
    while (i <= j) {
        while (A[i] < bound) ++i;
        while (bound < A[j]) --j;
        if (i <= j) swap(A[i++], A[j--]);
    }
    qSort(A, l, j);
    qSort(A, i, r);
}

int main() {
    int n;
    cin >> n;
    int A[500005] = {0};
    for (int i = 0; i < n; ++i) {
        scanf("%d", &A[i]);
    }
    //bubbleSort(A, n);
    //insertSort(A, n);
    //selectSort(A, n);
    mergeSort(A, 0, n);
    //qSort(A, 0, n-1);
    print(A, n);
    return 0;
}
