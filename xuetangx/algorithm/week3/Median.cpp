/*
问题描述 给定长度为 2 n − 1 的数组，对于每个 k = 1 , 2 , ... , n ，求出前 2 k − 1 个数的中位数。
输入格式
第一行一个正整数 n 。
接下来一行 2 n − 1 个正整数，表示所给数组。
输出格式 输出 n 行，第 i 行表示这个数组的前 2 i − 1 个数的中位数。
样例输入
3 8 7 6 9 9
样例输出 8 7 8
数据范围
对于 100 % 的数据，n ≤ 3 × 10 5 所有输入数据的数值都在 32 位整型范围内。
*/
#include <iostream>
#include <bits/stdc++.h>

using namespace std;

priority_queue<int, vector<int>, std::greater<int>> minp;
priority_queue<int> maxp;
int insert(int data) {
    if (data > minp.top()) {
        if (minp.size() > maxp.size()) {
            maxp.push(minp.top());
            minp.pop();
        }
        minp.push(data);
    }
    else {
        maxp.push(data);
        if (maxp.size() > minp.size()) {
            minp.push(maxp.top());
            maxp.pop();
        }
    }
}

int main() {
    int n;
    cin >> n;
    int temp = 0;
    cin >> temp;
    printf("%d\n", temp);
    minp.push(temp);
    for (int i = 1; i < 2 * n - 1; i += 2) {
        int temp1, temp2;
        scanf("%d %d", &temp1, &temp2);
        insert(temp1);
        insert(temp2);
        printf("%d\n", minp.top());
    }
    return 0;
}
