#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1e9 + 7;

int main() {
    int n;
    cin >> n;

    vector<int> dp(n + 1);
    dp[0] = 1;

    for (int i = 1; i <= n; i++) {
        long long res = 0;
        for (int j = 1; j <= min(i, 6); j++) {
            res = (res + dp[i - j]) % MOD;
        }
        dp[i] = res;
    }

    cout << dp[n] << '\n';
}