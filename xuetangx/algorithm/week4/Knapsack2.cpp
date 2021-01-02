#include <iostream>
#include <bits/stdc++.h>

using namespace std;

int AnsF[5005][5005] = {0};
int AnsB[5005][5005] = {0};
struct Good {
    int v;
    int w;
};
vector<Good> Vec;

void cul() {
    int size = Vec.size();
    for (int i = 1; i < size; ++i) {
        for (int j = 0; j < Vec[i].v; ++j) {
            AnsF[i][j] = AnsF[i-1][j];
        }
        for (int j = Vec[i].v; j < 5000; ++j) {
            AnsF[i][j] = max(AnsF[i-1][j], AnsF[i-1][j-Vec[i].v] + Vec[i].w);
        }
    }
    for (int i = size - 1; i > 0; --i) {
        for (int j = 0; j < Vec[i].v; ++j) {
            AnsB[i][j] = AnsB[i+1][j];
        }
        for (int j = Vec[i].v; j < 5000; ++j) {
            AnsB[i][j] = max(AnsB[i+1][j], AnsB[i+1][j-Vec[i].v] + Vec[i].w);
        }
    }
}

int main() {
    int n = 0;
    cin >> n;
    Good temp = {-1,-1};
    Vec.push_back(temp);
    for (int i = 0; i < n; ++i) {
        Good good;
        cin >> good.v >> good.w;
        Vec.push_back(good);
    }
    cul();
    int q;
    cin >> q;
    for (int i = 1; i <= q; ++i) {
        int V, x;
        cin >> V >> x;
        int ans = 0;
        for (int j = 0; j <= V; ++j) {
            ans = max(ans, AnsF[x-1][j] + AnsB[x+1][V-j]);
        }
        cout << ans << endl;
    }
}
