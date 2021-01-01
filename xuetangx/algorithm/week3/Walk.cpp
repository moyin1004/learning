#include <iostream>
#include <bits/stdc++.h>
using namespace std;
const int mod = 1e9+7;
typedef long long ll;

int table[2005][1005];
int C(int n, int m) {
    if (m == 0 || n == m) return 1;
    if (table[n][m]) return table[n][m];
    int ans = C(n-1,m-1) + C(n-1,m) % mod;
    table[n][m] = ans;
    return ans;
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        int n, x, y;
        cin >> n >> x >> y;
        if (n < x + y) {
            cout << 0 << endl;
        }
        else if (n == x + y) {
            cout << C(x+y, x) << endl;
        }
        else {
            
        }
    }
    return 0;
}