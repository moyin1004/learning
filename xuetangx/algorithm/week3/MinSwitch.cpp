#include <iostream>
#include <bits/stdc++.h>
using namespace std;

long long ans = 0;
void merge(vector<int> &A, int lo, int mi, int hi) {
    int temp[hi-lo+1];
    int pos = 0;
    int i = lo, j = mi;
    while (i < mi && j < hi) {
        if (A[i] <= A[j]) {
            temp[pos++] = A[i++];
        }
        else {
            ans += mi - i;
            temp[pos++] = A[j++];
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
void mergeSort(vector<int> &A, int lo, int hi) {
    if (hi - lo <= 1) {
        return ;
    }
    int mi = lo + (hi - lo) / 2;
    mergeSort(A, lo, mi);
    mergeSort(A, mi, hi);
    merge(A, lo, mi, hi);
}

int main() {
    int n;
    cin >> n;
    vector<int> a;
    for (int i = 0; i < n; ++i) {
        int temp;
        cin >> temp;
        a.push_back(temp);
    }
    mergeSort(a, 0, n);
    printf("%lld\n", ans);
}