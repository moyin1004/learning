/*
描述
给定一个n个整数的序列以及一个非负整数d，请你输出这个序列中有多少个连续子序列（长度大于1），满足该子序列的最大值最小值之差不大于d。
连续子序列：序列1 2 3中长度大于1的连续子序列有：
1 2
2 3
1 2 3
输入
第一行包含两个整数n,d。接下来一行包含n个整数。
输出
输出一个整数，表示满足条件的连续子序列个数。
样例1输入
8 5
5 5 4 8 -10 10 0 1
样例1输出
7
样例1解释
满足条件的连续子序列有：
5 5
5 5 4
5 5 4 8
5 4
5 4 8
4 8
0 1
限制
对于60%的数据，n ≤ 5000；
对于100%的数据，n ≤ 300000。
保证所有整数的绝对值不超过10^9，d不超过2×10^9。
*/

#include <iostream>
#include <bits/stdc++.h>

using namespace std;

const int N = 3e5+5;
int n, d, max_value[N], min_value[N];
vector<int> a;

long long solve(int l, int r) {
    if (1 == r - l) return 0;
    int mid = (l + r) >> 1;
    long long ans = solve(l, mid) + solve(mid, r);

    for (int i = mid; i < r; ++i) {
        min_value[i] = (i == mid) ? a[i] : min(min_value[i-1], a[i]);
        max_value[i] = (i == mid) ? a[i] : max(max_value[i-1], a[i]);
    }

    // 枚举左端点在[l, mid)上的符合条件的子序列
    int mn = 0, mx = 0, pos = r-1;
    for (int i = mid-1; i >= l && pos > mid-1; --i) {
        mn = (i == mid-1) ? a[i] : min(mn, a[i]);
        mx = (i == mid-1) ? a[i] : max(mx, a[i]);
        for (; pos >= mid && max(mx, max_value[pos]) - min(mn, min_value[pos]) > d; --pos);
        ans += pos - mid + 1;
    }
    return ans;
}

int main() {
    cin >> n >> d;
    for (int i = 0; i < n; ++i) {
        int temp;
        cin >> temp;
        a.push_back(temp);
    }
    cout << solve(0, n) << endl;
    return 0;
}