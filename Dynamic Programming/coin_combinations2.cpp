#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, x;
    cin >> n >> x;

    vector<int> c(n);
    for (int i = 0; i < n; i++) {
        cin >> c[i];
    }

    sort(c.begin(), c.end());

    long long MOD = 1e9 + 7;

    vector<long long> dp(x + 1);
    dp[0] = 1;

    for (int i = 0; i < n; i++) {
        for (int j = c[i]; j <= x; j++) {
            dp[j] = (dp[j] + dp[j - c[i]]) % MOD;
        }
    }

    cout << dp[x] << endl;
}