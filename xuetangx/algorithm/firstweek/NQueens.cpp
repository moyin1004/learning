/*
题目描述
N皇后问题是一个经典的问题，其目标是在一个N*N的棋盘上的每一行放置1个皇后，并使其不能互相攻击（同一行、同一列、同一斜线上的皇后都会自动攻击）。
现在，我们将棋盘上的一些位置挖洞，挖洞的位置不能放置棋子。此时，问一共有多少种可能的放置方法？
输入格式
输入第一行有一个整数N，表示棋盘大小。 接下来会有N行，每行有N个被空格隔开的整数，表示该棋盘位置是否有洞。（0为正常，1为有洞）。
输出格式
输出一行，包含一个整数，表示当前N皇后的放置方案数。
样例输入
4
1 1 0 1
0 0 0 0
0 0 0 0
0 0 0 0
样例输出
1
数据范围
1 <= N <= 10
*/

#include <iostream>
#include <bits/stdc++.h>

using namespace std;

int Num; // 方案数
int Q[11]; // 皇后所占用的行号，下标是皇后的列号，值是皇后的行号
bool S[11], L[21], R[21]; // 行，(i-j)，(i+j)对角线是否安全
int OFFSET; // 用来统一数组下标范围
int N;
bool CheckBoard[11][11] = {0};

void Try(int col) {
    // 终止条件
    if (col == N + 1) {
        ++Num;
        return ;
    }
    for (int row = 1; row <= N; row++) {
        // 判断拟放置皇后位置是否安全
        if (!S[row] || !R[col + row] ||
            !L[col - row + OFFSET] ||
            !CheckBoard[row][col]) {
            continue;
        }
        Q[col] = row; // 记录位置
        S[row] = false;
        L[col - row + OFFSET] = false;
        R[col + row] = false;

        Try(col + 1);
        // 回溯
        S[row] = true;
        L[col - row + OFFSET] = true;
        R[col + row] = true;
    }
}
int main() {
    Num = N = 0;
    cin >> N;
    OFFSET = N + 1;
    for (int i = 0; i <= N; ++i) S[i] = true;
    for (int i = 0; i < 21; ++i) L[i] = R[i] = true;
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j) {
            bool isHole = true;
            cin >> isHole;
            CheckBoard[i][j] = !isHole;
        }
    }

    Try(1); // 从第一列开始
    cout << Num << endl;
}
