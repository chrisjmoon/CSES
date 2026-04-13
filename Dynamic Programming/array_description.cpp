#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;

    vector<int> x(n);
    for (int i = 0; i < n; i++)
    {
        cin >> x[i];
    }

    vector<vector<long long>> dp(n, vector<long long>(m + 1, 0));
    long long MOD = 1e9 + 7;

    for (int i = 0; i < n; i++)
    {
        if (i == 0)
        {
            if (x[i] != 0)
            {
                dp[i][x[i]] = 1;
            }
            else
            {
                for (int j = 1; j <= m; j++)
                {
                    dp[i][j] = 1;
                }
            }
            continue;
        }
        if (x[i] != 0)
        {
            if (x[i] > 1)
            {
                dp[i][x[i]] = (dp[i][x[i]] + dp[i - 1][x[i] - 1]) % MOD;
            }
            dp[i][x[i]] = (dp[i][x[i]] + dp[i - 1][x[i]]) % MOD;
            if (x[i] < m)
            {
                dp[i][x[i]] = (dp[i][x[i]] + dp[i - 1][x[i] + 1]) % MOD;
            }
            continue;
        }

        for (int j = 1; j <= m; j++)
        {
            if (j > 1)
            {
                dp[i][j] = (dp[i][j] + dp[i - 1][j - 1]) % MOD;
            }
            dp[i][j] = (dp[i][j] + dp[i - 1][j]) % MOD;
            if (j < m)
            {
                dp[i][j] = (dp[i][j] + dp[i - 1][j + 1]) % MOD;
            }
        }
    }

    long long res = 0;
    for (int i = 1; i <= m; i++)
    {
        res = (res + dp[n - 1][i]) % MOD;
    }

    cout << res << endl;
}