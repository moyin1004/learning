/*
问题描述
小粽今晚在数星星。
小粽把整个天空看作一个平面，她测出了她看见的每个星星的坐标，第 i 颗星星的坐标为 ( x i , y i ) 。 光数星星实在是太无聊了，小粽想知道，对于每颗星星，其左下方的星星的数量，即对于每个 i ，小粽想要知道满足 j ≠ i ，且 x j ≤ x i , y j ≤ y i 的 j 的数量。
输入格式
第一行一个正整数 n ，表示星星的数量。
接下来 n 行，每行两个正整数 x i , y i ，表示第 i 颗星星的坐标。
输出格式
输出共 n 行，每行输出一个正整数，表示第 i 颗星星左下方星星的数量。
输入样例1
5
1 1
5 1
7 1
3 3
5 5
输出样例1
0
1
2
1
3
数据规模及约定
对于 30 % 的数据有 n ≤ 500 ；  对于 60 % 的数据有 n ≤ 8000 ；
对于 100 % 的数据有 n ≤ 3 × 10^5，所有坐标都在 int 范围内，不存在两个不同的点有相同的坐标。
提示
[回想一下归并求逆序对咋做的？你就会做这个题辣]
[有兴趣的同学百度二维偏序~]
*/

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

struct Star {
    int x;
    int y;
    int pos;
    Star() : x(0), y(0), pos(0) {}
    Star(int x, int y, int pos) : x(x), y(y), pos(pos) {}
    friend bool operator<(Star &a, Star &b) {
        if (a.x < b.x) return true;
        if (a.x == b.x && a.y < b.y) return true;
        return false;
    }
};

int ans[300005];

void merge(vector<Star> &A, int lo, int mi, int hi) {
    Star temp[hi-lo+1];
    int pos = 0;
    int i = lo, j = mi;
    while (i < mi && j < hi) {
        if (A[i].y > A[j].y) {
            temp[pos++] = A[i++];
        }
        else {
            ans[A[j].pos] += mi - i;
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
void mergeSort(vector<Star> &A, int lo, int hi) {
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
    vector<Star> a;
    for (int i = 0; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        a.push_back(Star(x, y, i));
    }
    // 排序第一维
    sort(a.begin(), a.end());
    // 求第二维应降序排列的逆序对数量
    mergeSort(a, 0, n);
    for (int i = 0; i < n; ++i) {
        printf("%d\n", ans[i]);
    }
}