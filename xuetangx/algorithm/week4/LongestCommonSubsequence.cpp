/*
问题描述
给定两个 1 到 n 的排列 A,B （即长度为 n 的序列，其中 [1,n] 之间的所有数都出现了恰好一次）。
求它们的最长公共子序列长度。

输入格式
第一行一个整数 n ，意义见题目描述。
第二行 n 个用空格隔开的正整数 A[1],…,A[n]，描述排列 A。
第三行 n 个用空格隔开的正整数 B[1],…,B[n]，描述排列 B。
输出格式
一行一个整数，表示 A,B 的最长公共子序列的长度。

样例输入
5
1 2 4 3 5
5 2 3 4 1
样例输出
2
样例解释
(2,3) 和 (2,4) 都可以是这两个序列的最长公共子序列。

数据范围
对于 80% 的数据，保证 n<=5,000。
对于 100% 的数据，保证 n<=50,000。
提示
[把 A 中的所有数替换成其在 B 中出现的位置，想一想，新序列的最长上升子序列和所求的东西有什么关系呢？]
*/

#include <bits/stdc++.h>
using namespace std;

const int N = 5*10e4+5;
int a[N];
int b[N];

int getAnswerDP(int n) {
    int dp[2][n+1];
    int cnt = 1, prev = 0;
    memset(dp, 0, sizeof(dp));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (b[j] == a[i]) dp[cnt][j] = dp[prev][j-1] + 1;
            else dp[cnt][j] = max(dp[cnt][j-1], dp[prev][j]);
            // cout << dp[i][j] << " ";
        }
        swap(cnt, prev);
        // cout << endl;
    }
    return dp[cnt][n];
}


// 最长公共子序列解法
const int INF = 1e9;
int getAnswer(int n) {
    vector<int> pos, f;
    pos.resize(n+1, INF);
    f.resize(n+2, INF);
    for (int i = 1; i <= n; ++i) {
        pos[b[i]] = i;
    }
    for (int i = 1; i <= n; ++i) {
        a[i] = pos[a[i]];
    }
    f[0] = 0;
    for (int i = 0; i <= n; ++i) {
        // 二分，插入a[i]并更新f
        *lower_bound(f.begin(), f.end(), a[i]) = a[i];
    }
    return int(lower_bound(f.begin(), f.end(), n+1) - f.begin()) - 1;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= n; ++i) cin >> b[i];
    cout << getAnswer(n) << endl;
    return 0;
}