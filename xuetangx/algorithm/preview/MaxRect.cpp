/*
问题描述
有一个直方图，横轴长度为 n，第 i 列的高度为 h[i]。
请你求出在这个直方图中面积最大的子矩阵。
输入格式
第一行一个正整数 n。
第二行 n 个用空格隔开的非负整数，依次描述 h[1],h[2],…,h[n]。
输出格式
输出一行一个数，表示最大面积。
样例输入
5
2 3 3 3 2
样例输出
10
数据范围
对于 30% 的测试点，保证 n<=4。
对于 70% 的测试点，保证 n<=1000。
对于所有测试点，保证 n<=50000。
保证所有 h[i] 不超过 32767。
*/

#include <iostream>
#include <bits/stdc++.h>

using namespace std;
static const int MAX = 50005;

int culRect(int H[], stack<int> &M, int maxH) {
    int temp = M.top();
    M.pop();
    int minH = M.empty() ? -1 : M.top();
    return H[temp] * (maxH - minH - 1);
}

int main() {
    stack<int> M;
    int H[MAX];
    int n = 0;
    cin >> n;
    int maxRect = 0;
    for (int i = 0; i < n; ++i) {
        cin >> H[i];
    }
    for (int i = 0; i < n;) {
        if (M.empty() || H[M.top()] <= H[i]) {
            M.push(i);
            ++i;
        }
        else {
            maxRect = max(maxRect, culRect(H, M, i));
        }
    }
    while (!M.empty()) {  // cal extra data of stack
        maxRect = max(maxRect, culRect(H, M, n));
    }
    cout << maxRect << endl;
    return 0;
}

// reference answer
int getAnswer(int n, int *H) { //  indices for H elements are based on 1-origin
    int ans = 0;
    stack<int> M;
    M.push(0); // guard
    for (int i = 1; i <= n + 1; ++i) {
        while (H[M.top()] > H[i]) {
            int nowHeight = H[M.top()];
            M.pop();
            ans = max(ans, nowHeight * (i - M.top() - 1));
        }
        M.push(i);
    }
    return ans;
}
