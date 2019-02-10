/// @file    mergesort.cc
/// @data    2019-01-22 20:33:41

#include <iostream>

using std::min;
using std::cout;
using std::endl;

const int maxn = 100;
void merge(int A[], int L1, int R1, int L2, int R2) {
    int i = L1, j = L2;
    int temp[maxn], index = 0;

    while(i <= R1 && j <= R2) {
        if(A[i] < A[j]) temp[index++] = A[i++];
        else temp[index++] = A[j++];
    }

    //添加剩余元素
    while(i <= R1) temp[index++] = A[i++];
    while(j <= R2) temp[index++] = A[j++];
    for(int i = 0; i < index; i++) {
        A[L1 + i] = temp[i];
    }
}
//递归
void mergeSort(int A[], int left, int right) {
    if(left < right) {
        int mid = (left + right) / 2;
        mergeSort(A, left, mid);
        mergeSort(A, mid + 1, right);
        merge(A, left, mid, mid + 1, right);
    }
}
//非递归
void mergeSort(int A[], int n) {
    for(int step = 2; step / 2 <= n; step *= 2) {
        for(int i = 0; i < n; i += step) {
            //每step一组排序
            int mid = i + step / 2 - 1;
            if(mid + 1 < n) merge(A, i, mid, mid + 1, min(i + step - 1, n - 1));
        }
    }
}


int main() {
    int a[] = {22, 434, 4, 84, 34, 43, 875, 35, 56};
    mergeSort(a, 9);
    cout << "非递归版本:" << endl; 
    for (auto &elem : a)
        cout  << elem << endl;
    int b[] = {22, 434, 4, 84, 34, 43, 875, 35, 56};
    mergeSort(b, 0, 8);
    cout << "递归版本:" << endl; 
    for (auto &elem : b)
        cout  << elem << endl;

    return 0;
}
