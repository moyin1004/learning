/*
题目描述
有一排n个格子，现在想用红黄蓝绿四种颜色给格子染色。但是，红色和绿色必须染成偶数个，问总共有多少种方案？
输入格式
一行一个整数n。
输出格式
一行一个整数，表示对答案对10^9+7取模的值。
数据范围1≤n≤105，答案对10^9+7取模。
样例1
Input
2
Output
6
样例1解释
要么用红和绿染所有格子，要么用蓝和黄任意染格子，共2+2^2=6种方案。
样例2
Input
100000
Output
847835584
解题提示
虽然最终答案在 32 位整型范围内，但是计算乘法的时候需要用 64 位整型才不会溢出。
*/

#include <iostream>
#include <bits/stdc++.h>
using namespace std;
const int mod = 1e9+7;
typedef long long ll;

ll Pow(ll a, ll b) {
    if (b == 0) return 1;
    if (b % 2 == 1) {
        return a * Pow(a, b-1) % mod;
    }
    else {
        ll mul = Pow(a, b/2);
        return mul * mul % mod;
    }
}

int main() {
    long long n;
    cin >> n;
    cout << (Pow(4, n-1) + Pow(2, n-1)) % mod << endl;
}