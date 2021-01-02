#include <iostream>
#include <bits/stdc++.h>
#include <cmath>

using namespace std;

int Ans = 99999999;
int N, M, T, D;
bool status[2005][2005] = {false};
int level[2005][2005] = {0};      // 记录访问某状态时的层次，深层次不能影响浅层次

void move(int &a, int &b, int idx) {
    int sum = a + b;
    if (idx == 1) {
        a = max(0, a-M+b);
        b = min(sum, M);
    }
    else {
        b = max(0, b-N+a);
        a = min(sum, N);
    }
}
void add(int &cur, int idx) {
    if (idx == 1) cur = N;
    else cur = M;
}
void drop(int &cur, int idx) {
    cur = 0;
}

bool Try(int n, int m, int num) {
    Ans = min(Ans, abs(D-m-n));
    if (Ans == 0) return true;
    if (status[n][m] && level[n][m] < num) return false;
    status[n][m] = true;
    level[n][m] = num;
    //cout << n << " "<< m << " "<< num <<endl;
    if (num == T) {
        return false;
    }

    int tempn = n;
    int tempm = m;
    if (n != N) {
        add(n, 1);
        if (Try(n, m, num+1)) return true;
    }
    n = tempn;
    if (m != M) {
        add(m, 2);
        if (Try(n, m, num+1)) return true;
    }
    m = tempm;
    if (n != 0) {
        drop(n, 1);
        if (Try(n, m, num+1)) return true;
    }
    n = tempn;
    if (m != 0) {
        drop(m, 2);
        if (Try(n, m, num+1)) return true;
    }
    m = tempm;

    if (m != M && n != 0) {
        move(n, m, 1);
        if (Try(n, m, num+1)) return true;
    }
    m = tempm;
    n = tempn;
    if (n != N && m != 0) {
        move(n, m, 2);
        if (Try(n, m, num+1)) return true;
    }
    status[n][m] = false;
    return false;
}

int main() {
    cin >> N >> M >> T >> D;
    Try(0, 0, 0);
    cout << Ans << endl;
    return 0;
}
