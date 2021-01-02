/*
描述
n种物品，每种物品有相应的价值和体积，同时物品还分为两类，一类是“单个物品”，即该种物品只有一个；一类是“多个物品”，即该种物品有无限个。
现在你有一个体积为V的背包，那么该装些什么物品到背包里使得价值之和最大呢？
输入
第一行包含两个正整数n,V。
接下来n行，每行代表一种物品。每行的第一个数字表示该物品的种类（若为0表示“单个物品”，若为1表示“多个物品”），
第二个数字表示该物品的价值，第三个数字表示该物品的体积。
输出
输出一个整数，表示最大的价值之和。
样例1输入
5 8
0 6 8
0 7 3
1 1 1
0 8 1
0 5 2
样例1输出
22
样例1解释
第三种物品有无限个，其余都是单个物品。
若我们放入物品1，则背包已经装满，此时价值和为6；
若我们放入物品2、4、5，背包所剩体积为8-3-1-2=2，此时价值和为7+8+5=20；
若我们放入8个物品3，背包装满，此时价值之和为8×1=8；
若我们放入物品2、4、5，再放两个物品3，则背包装满，此时价值和为7+8+5+2×1=22。
可以验证，最优答案就是22。
限制
对于30%的数据，n,V ≤ 20；
对于100%的数据，n,V ≤ 5000。
保证数据中所有的整数均为正整数，且不超过5000。
提示
[经典的01背包和完全背包问题。]
*/

#include <iostream>
#include <bits/stdc++.h>

using namespace std;

struct Good {
    int count;
    int w;
    int c;
};

int ans[5005];
vector<Good> goods;

int main() {
    int n, V;
    cin >> n >> V;
    for (int i = 0; i < n; ++i) {
        Good good;
        cin >> good.count >> good.w >> good.c; 
        goods.push_back(good);
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 1; j <= V; ++j) {
            // Unbounded Knapsack state transfer
            if (goods[i].count == 1 && j - goods[i].c >=0) {
                ans[j] = max(ans[j], ans[j-goods[i].c] + goods[i].w);
            }
            // 0-1 Knapsack state transfer
            int pos = V - j + 1;
            if (goods[i].count == 0 && pos-goods[i].c >= 0) {
                ans[pos] = max(ans[pos], ans[pos-goods[i].c] + goods[i].w);
            }
        }
    }
    cout << ans[V] << endl;
}