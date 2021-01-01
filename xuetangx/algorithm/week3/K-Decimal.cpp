/*
题目描述
这是一道很简单的问题。给你一个长度为 n 的序列 a1,a2,...,an，求这个序列的第 k 小的数。k 小数的定义为：将 a 从小到大排序后第 k 个位置的值。
由于输入数据量过大，输入只给出a1的值，并采用如下递推式生成剩余数据：ai=(pai−1+q)modM(1<i≤n)
其中，mod 运算的含义是：a mod b 的值为 a 除以 b 得到的余数。
输入格式
输入第一行为两个正整数 n,k，含义见描述。
第二行为四个非负整数 a1,p,q,M，你需要根据题目中给出式子计算完整序列。
输出格式
输出一行一个正整数，表示第原序列第 k 小的数。
输入样例1
5 4
6 7 5 10
输出样例1
6
数据范围
对于 20% 的数据，n≤102；
对于40% 的数据，n≤104；
对于 60% 的数据，n≤106；
对于100% 的数据，1≤k≤n≤3×107，输入中其它数都在 int 范围内。
*/

#include <iostream>

using namespace std;
typedef long long ll;
const int MAX = 3e7+5;
ll A[MAX];

ll quickSlect(int n, int k) {
    for (int lo = 0, hi = n-1; lo < hi; ) {
        int i = lo, j = hi;
        ll pivot = A[lo];
        while (i < j) {
            while (i < j && pivot <= A[j]) --j;
            A[i] = A[j];
            while (i < j && pivot >= A[i]) ++i;
            A[j] = A[i];
        }
        A[i] = pivot;
        if (k <= i) hi = i - 1;
        if (i <= k) lo = i + 1;
    }
    return A[k];
}

int main() {
    int n, k;
    cin >> n >> k;
    ll a1, p, q, M;
    cin >> a1 >> p >> q >> M;
    A[0] = a1;
    for (int i = 1; i < n; ++i) {
        A[i] = (p * A[i-1] % M + q % M) % M;
    }
    cout << quickSlect(n, k-1) << endl;
    return 0;
}