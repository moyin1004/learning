/*
题目描述
小Z有n枚硬币，面值分别为w1 , w2 , ⋯ , wn。请问他总共有多少种办法凑出v块钱？
请注意，相同面值的硬币我们也认为是不同的。
输入格式
第一行两个整数n,v，含义如题所述；
第二行n个整数，第i个整数为wi，表示第i个硬币的面值。
输出格式
一行一个整数，表示答案。特别地，如果没有合法方案，输出0。
数据范围
1 ≤ n ≤ 30 , 1 ≤ v ≤ 900 , ∀ i , 1 ≤ wi ≤ 30 。
样例1
Input
4 6
1 2 4 4
Output
2
样例1解释
有两种选法：
选2号、3号硬币；
选2号、4号硬币。
样例2
Input
21 315
28 26 26 24 10 26 30 4 26 5 21 17 18 7 11 12 16 8 6 30 8
Output
123
*/

#include <iostream>
#include <bits/stdc++.h>

using namespace std;

const int N = 30;
int f[N+1][N*N+1];

int main() {
    int n, v;
    int sum = 0;
    scanf("%d %d", &n, &v);
    vector<int> vec;
    for (int i = 0; i < n; ++i) {
        int temp;
        scanf("%d", &temp);
        sum += temp;
        vec.push_back(temp);
    }
    // 母函数，求v次方的系数
    f[0][0] = 1;
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= sum; ++j) {
            f[i][j] = f[i-1][j];
            if (j >= vec[i-1]) {
                f[i][j] += f[i-1][j-vec[i-1]]; 
            }
        }
    }
    printf("%d\n", f[n][v]);

    return 0;
}

/*
// Brute Force
vector<int> vec;
int Num = 0;
void Try(int i, int v) {
    long long sum = 0;
    sum += vec[i];
    int n = vec.size();
    for (int k = i+1; k < n; ++k) {
        if (sum == v) ++Num;
        if (sum > v) {
            for (int j = i+1; j < k; ++j) {
                sum -= vec[j];
                if (sum == v) {
                    ++Num;
                    break;
                }
                if (sum < v) break;
            }
        }
        sum += vec[k];
    }
}

int main () {
    int n, v;
    scanf("%d %d", &n, &v);
    for (int i = 0; i < n; ++i) {
        int temp;
        scanf("%d", &temp);
        vec.push_back(temp);
    }
    sort(vec.begin(), vec.end());
    for (int i = 0; i < n; ++i) {
        Try(i,v);
    }
    printf("%d\n", Num);
    return 0;
}
*/