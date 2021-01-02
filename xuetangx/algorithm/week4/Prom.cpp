#include <iostream>
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 21;
int a[N], b[N];
ll FacTable[N+1];
int match_girl[N]; // girl[i]'s match
int match_boy[N];

void fac(int n) {
    FacTable[0] = 1;
    for (int i = 1; i <= n; ++i) {
        FacTable[i] = FacTable[i-1] * i;
    }
}

ll calc(int m, int free_cnt) {
    if (m == 0) {
        return FacTable[free_cnt];
    }
    ll ans = calc(m-1, free_cnt);
    // a[m], b[m]
    if (match_girl[a[m]] == 0 && match_boy[b[m]] == 0) {
        match_girl[a[m]] = b[m];
        match_boy[b[m]] = a[m];
        ans -= calc(m-1, free_cnt-1);
        match_girl[a[m]] = 0;
        match_boy[b[m]] = 0;
    }
    return ans;
}

int main() {
    int n, m;
    cin >> n >> m;
    fac(n);
    for (int i = 1; i <= m; ++i) {
        cin >> a[i] >> b[i];
    }
    ll ans = calc(m, n);
    printf("%lld\n", ans);
    return 0;
}
