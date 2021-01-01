/*
题目描述
小Z有 n 块一模一样的正方体积木，他要把这些积木放到 m × m 的网格中。
每块积木要么放到恰好一个格子上，要么叠到另一块积木上。好奇的他想知道，有多少种把这 n 块积木都放进网格的摆法？
输入格式
一行两个整数 n , m ，分别表示积木的数量和网格的边长。
输出格式
一行一个整数，表示答案对 10^9 + 7 取模的结果。  数据范围 1 ≤ n ≤ 1000 , 1 ≤ m ≤ 30
样例1
Input 2 2
Output 10
样例1解释
有两块积木，要放到 2 × 2 的网格中。将两块积木叠在一起有C(4,1) = 4 种方法，两个积木分开放有 C(4,2) = 6 种方法，共 10 种。
样例2
Input 1000 30
Output 443860595
*/

#include <bits/stdc++.h>
using namespace std;
const int mod = 1e9+7;

typedef long long ll;

int table[2000];
int C(int n, int m) {
    table[0] = 1;
    for (int i = 1; i <= n; ++i) {
        for (int j = i; j >= 1; --j) {
            table[j] = (table[j-1] + table[j]) % mod;
        }
    }
    return table[m];
}

int main() {
    int n, m;
    cin >> n >> m;
    cout << C(n+m*m-1, n) << endl;
}

// int dp[1005][1005];
// int main()
// {
//     int n,m;
//     while(scanf("%d %d",&n,&m )!=EOF)
//     {
//         dp[0][1] =1 ;
//         m*=m;

//         for(int i=1;i<=m;i++)
//         {
//             for(int j = 1;j<=n+1;j++)
//             {
//                 dp[i][j] = dp[i-1][j] + dp[i][j-1];
//                 dp[i][j] %= mod;
//             }
//         }
//         cout<<dp[m][n+1]<<endl;
//     }
// }
