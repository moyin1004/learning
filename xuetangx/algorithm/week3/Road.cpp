/*
题目描述
用1×1的方砖，2×2的方砖，两个直角边都为2的三角形，给3×n的路铺面，请问共有多少种方法？
输入格式
一行一个整数n，含义如题所述。
输出格式
输出一个值，表示答案乘5模10^9+7的值。
数据范围
1≤n≤109
样例1
Input
2
Output
35
样例1解释
一共有7种合法方案，乘5再模109+7的值为35。
样例2
Input
1000000000
Output
989068937
解题提示
模P意义下，负数−a等价于P−a。
*/

#include <bits/stdc++.h>
#include <cassert>
using namespace std;

typedef long long ll;
const int Mod = 1e9+7;

struct Matrix {
    int a[2][2];
    friend Matrix operator*(const Matrix &a, const Matrix &b) {
        Matrix c;
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j) {
                long long v = 0;
                for (int k = 0; k < 2; ++k) {
                    v = (v + (long long)a.a[i][k] * b.a[k][j]) % Mod;
                }
                c.a[i][j] = v;
            }
        }
        return c;
    }
};

Matrix fpow(Matrix a, int n) {
    if (n == 0) {
        return {1, 0, 0, 1};
    }
    Matrix ans = fpow(a, n/2);
    ans = ans * ans;
    if (n % 2 == 1) {
        ans = ans * a;
    }
    return ans;
}

ll fpow(ll a, ll n) {
    if (n == 0) {
        return 1;
    }
    ll ans = fpow(a, n/2);
    ans = ans * ans % Mod;
    if (n % 2 == 1) {
        ans = ans * a % Mod;
    }
    return ans;
}

int main() {
    int n = 0;
    scanf("%d", &n);
    // 矩阵求解
//    Matrix A = {1, 6, 1, 0};
//    A = fpow(A, n);
//    int ans = A.a[0][0];
//    ans = (long long)ans * 5 % Mod;
    // 通项公式求解
    long long ans = (fpow(3, n+1) % Mod + 2*fpow(-2, n) % Mod) % Mod;
    if (ans < 0) {
        // assert(0);
        ans = Mod + ans;
    }
    printf("%lld\n", ans);
    return 0;
}