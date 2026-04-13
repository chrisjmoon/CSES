#include <bits/stdc++.h>
using namespace std;

int main()
{
    int t;
    cin >> t;

    vector<int> n(t);
    int m = 0;
    for (int i = 0; i < t; i++)
    {
        cin >> n[i];
        m = max(m, n[i]);
    }

    vector<vector<long long>> dp(m + 1, vector<long long>(2, 0));
    long long MOD = 1e9 + 7;

    dp[1][0] = 1;
    dp[1][1] = 1;
    for (int i = 2; i <= m; i++)
    {
        dp[i][0] = (2 * dp[i - 1][0] + dp[i - 1][1]) % MOD;
        dp[i][1] = (dp[i - 1][0] + 4 * dp[i - 1][1]) % MOD;
    }

    for (int i = 0; i < t; i++)
    {
        cout << (dp[n[i]][0] + dp[n[i]][1]) % MOD << endl;
    }
}