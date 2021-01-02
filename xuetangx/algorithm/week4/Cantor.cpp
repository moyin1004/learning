#include <iostream>
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int N = 20;
ll FacTable[N];

void fac(int n) {
    FacTable[0] = 1;
    for (int i = 1; i < n; ++i) {
        FacTable[i] = FacTable[i-1] * i;
    }
}

ll get_rank(int n, vector<int> &a) {
    ll rank = 0;
    for (int i = 1; i <= n; ++i) {
        int cnt = 0;
        for (int j = 1; j <= i; ++j) {
            cnt += a[j] <= a[i];
        }
        rank += (a[i] - cnt) * FacTable[n-i];
    }
    return rank;
}

void get_perm(int n, ll rank, vector<int> &a) {
    bool vis[n+1] = {0};
    for (int i = 1; i <= n; ++i) {
        int cur_rank = rank / FacTable[n-i] + 1;
        int cur_cnt = 0;
        for (int j = 1; ; ++j) {
            if (vis[j]) continue;
            ++cur_cnt;
            if (cur_cnt == cur_rank) {
                a[i] = j;
                break;
            }
        }
        vis[a[i]] = true;
        rank %= FacTable[n-i];
    }
}

int main() {
    int n, step;
    cin >> n >> step;
    fac(n);
    vector<int> a(n+1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    ll rank = get_rank(n, a);
    rank += step;
    get_perm(n, rank, a);
    for (int i = 1; i <= n; ++i) {
        cout << a[i];
        if (i != n) {
            putchar(' ');
        }
    }
    cout << endl;
    return 0;
}


