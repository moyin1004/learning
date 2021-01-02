/*
问题描述
给定长度为 n 的数组 a，其中每个元素都为 [0,2^k) 之间的整数，请求出它们在实数轴上相邻两个数之间的最大值（即maxGap）。
由于 n 可能很大，为了避免过大的输入、输出规模，我们会在程序内部生成数据，并要求你输出排序后序列的哈希值。具体方法如下（用c++代码展示）：
输入将会给定 n,k,seed。
你可以调用 initData(a,n,k,seed) 来获得需要排序的 a 数组。

输入格式
一行 3 个用空格隔开的整数 n,k,seed，意义见题目描述。
输出格式
一行一个整数，表示最大间隙（即maxGap）。
样例输入
5 4 233333
样例输出
5
样例解释
生成的序列应为 4 10 13 9 4，最大间隙为 9-4=5。
数据范围
本题共设置 4 组数据。
对于第 1 组数据，保证 n=1000，k=16。
对于第 2 组数据，保证 n=5*10^6，k=32。
对于第 3 组数据，保证 n=2^26=67,108,864，k=16。
对于第 4 组数据，保证 n=2^26=67,108,864，k=32。
保证给定的 seed 在 32 位无符号整数的范围内。
提示
[对于 k=16 的数据，使用桶排序即可。]
[对于 k=32 的数据，可以用邓老师上课讲的算法哦！]
[进一步地，如何设置桶的大小来避免较慢的除法运算呢？（提示：可以考虑位运算！）]
Source
[数据生成器来自：「WC2017」挑战（[[https://loj.ac/problem/2286]]）]
*/
#include <iostream>
#include <bits/stdc++.h>
#include <cassert>

using namespace std;

typedef unsigned int u32;
u32 nextInt(u32 x){
	x^=x<<13;
	x^=x>>17;
	x^=x<<5;
	return x;
}
void initData(u32 *a,int n,int k,u32 seed){
	for (int i=0;i<n;++i){
		seed=nextInt(seed);
		a[i]=seed>>(32-k);
	}
}

const int MAXN = 67108870;

u32 a[MAXN];
u32 bucket[MAXN][2];

int main() {
    u32 n, k, seed;
    cin >> n >> k >> seed;
    initData(a, n, k, seed);

    u32 maxn = a[0], minn = a[0];
    for (int i = 1; i < n; ++i) {
        maxn = max(maxn, a[i]);
        minn = min(minn, a[i]);
    }
    u32 range = maxn - minn;
    u32 count = range / (n-1) + 1;

    // init
    for (int i = 0; i <= n; ++i) {
        bucket[i][0] = maxn + 1;
        bucket[i][1] = 0;
    }
    // 放入桶中
    for (int i = 0; i < n; ++i) {
        u32 pos = (a[i] - minn) / count;
        if (pos >= n + 1) {
            assert(0);
        }
        bucket[pos][0] = min(bucket[pos][0], a[i]);
        bucket[pos][1] = max(bucket[pos][1], a[i]);
    }
    u32 ans = 0;
    int cur = 0;
    for (int i = 1; i <= n; ++i) {
        // 过滤空桶
        if (bucket[i][0] == maxn + 1 && bucket[i][1] == 0) {
            continue;
        }
        ans = max(ans, bucket[i][0]-bucket[cur][1]);
        cur = i;
    }
    cout << ans << endl;
}