#include <iostream>
#include <bits/stdc++.h>

using namespace std;
const int MAXN = 20;

int Num; // 方案数
int Q[MAXN]; // 皇后所占用的行号，下标是皇后的列号，值是皇后的行号
bool S[MAXN], L[MAXN*2], R[MAXN*2]; // 行，(i-j)，(i+j)对角线是否安全
int OFFSET; // 用来统一数组下标范围
int N;

void Try(int col) {
    // 终止条件
    if (col == N + 1) {
        ++Num;
        return ;
    }
    for (int row = 1; row <= N; row++) {
        // 判断拟放置皇后位置是否安全
        if (!S[row] || !R[col + row] ||
            !L[col - row + OFFSET]) {
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
    for (int i = 0; i < N*2+1; ++i) L[i] = R[i] = true;

    Try(1); // 从第一列开始
    cout << Num << endl;
}
