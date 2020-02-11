/*
问题描述
有一个 n*m 的棋盘，棋盘上的每个点都是红的或绿的。
你需要找出一个面积最大的矩形区域，使得其中没有绿的格子。
输入格式
第一行 2 个正整数 n,m，描述棋盘尺寸。
接下来 n 行描述这个棋盘，每行 m 个字符，每个字符为 . 或 X，其中 . 表示这个位置是红色的，X 表示这个位置是绿色的。
输出格式
一行一个整数，表示最大面积。
样例输入
4 5
.....
XXXXX
.X...
.....
样例输出
6
样例解释
以第 3 行第 3 列的方格为左上角，第 4 行第 5 列的方格为右下角的矩形区域是全红的矩形中面积最大的。
数据范围
对于 30% 的数据，n,m<=100；
对于 60% 的数据，n,m<=400；
对于 85% 的数据，n,m<=1,000；
对于 100% 的数据，n,m<=1,500。
*/

#include <iostream>
#include <bits/stdc++.h>

using namespace std;

int getAnswer(int n, int *H) { //  indices for H elements are based on 1-origin
    int ans = 0;
    stack<int> M;
    M.push(0); // guard
    for (int i = 1; i <= n + 1; ++i) {
        while (H[M.top()] > H[i]) {
            int nowHeight = H[M.top()];
            M.pop();
            ans = max(ans, nowHeight * (i - M.top() - 1));
        }
        if (H[M.top()] == H[i]) {
            continue;
        }
        if (H[M.top()] == H[i - 1]) {
            M.push(i - 1);
        }
        M.push(i);
    }
    return ans;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    int maxRect = 0;
    int H[1505] = {0};
    for (int i = 0; i < n; ++i) {
        getchar();
        for (int j = 0; j < m; ++j) {
            char temp;
            scanf("%c", &temp);
            if (temp == 'X') {
                H[j+1] = 0;
            }
            else {
                H[j+1] += 1;
            }
        }
        maxRect = max(maxRect, getAnswer(m, H)); // run MaxRect per line
    }
    printf("%d\n", maxRect);
    return 0;
}
