#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<long long> dp(n + 1, 0);
    for (int i = 1; i < min(n + 1, 10); i++) {
        dp[i] = 1;
    }

    for (int i = 10; i <= n; i++) {
        int j = i;
        long long res = 1e9;
        while (j > 0) {
            int d = j % 10;
            if (d != 0) {
                res = min(res, dp[i - d]);
            }
            j = j / 10;
        }
        dp[i] = res + 1;
    }

    cout << dp[n] << endl;
}