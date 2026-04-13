#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, x;
    cin >> n >> x;

    vector<int> c(n);
    for (int i = 0; i < n; i++) {
        cin >> c[i];
    }

    long long MOD = 1e9 + 7;

    vector<long long> dp(x + 1, 0);
    dp[0] = 1;
    for (int i = 0; i <= x; i++) {
        for (int j = 0; j < n; j++) {
            if (i >= c[j]) {
                dp[i] = (dp[i] + dp[i - c[j]]) % MOD;
            }
        }
    }

    cout << dp[x] << endl;
}