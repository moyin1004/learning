#include <bits/stdc++.h>
using namespace std;

int n;
int getAnswer(vector<int> &data) {
    int dp[n+1][n+1];
    memset(dp, 0, sizeof(dp));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= i; ++j) {
            int pos = (i-1)*i/2 + j - 1;
            dp[i][j] = max(dp[i-1][j-1], dp[i-1][j]) + data[pos];
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        ans = max(ans, dp[n][i]);
    }
    return ans;
}

int main() {
    cin >> n;
    vector<int> data;
    for (int i = 0; i < n*(n+1)/2; ++i) {
        int temp;
        cin >> temp;
        data.push_back(temp);
    }
    cout << getAnswer(data) << endl;
    return 0;
}