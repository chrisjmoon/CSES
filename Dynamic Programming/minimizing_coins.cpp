#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, x;
    cin >> n >> x;

    vector<int> coins(n);
    for (int i = 0; i < n; i++) {
        cin >> coins[i];
    }
    sort(coins.begin(), coins.end());

    const long long s = 1e9;
    vector<long long> dp(x + 1, s);
    dp[0] = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= x; j++) {
            if (j >= coins[i]) {
                dp[j] = min(dp[j], dp[j - coins[i]] + 1);
            }
        }
    }

    if (dp[x] == s) {
        cout << -1 << '\n';
    } else {
        cout << dp[x] << '\n';
    }
}