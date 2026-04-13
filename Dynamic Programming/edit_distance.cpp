#include <bits/stdc++.h>
using namespace std;

int main()
{
    string s, t;
    cin >> s >> t;
    int n, m;
    n = s.size();
    m = t.size();

    if (n < m)
    {
        swap(s, t);
        swap(n, m);
    }

    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 1e9));
    for (int i = 0; i <= n; i++)
    {
        dp[i][0] = i;
    }
    for (int i = 0; i <= m; i++)
    {
        dp[0][i] = i;
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            int res = 1e9;
            res = min(res, dp[i - 1][j - 1] + (s[i - 1] != t[j - 1]));
            res = min(res, dp[i - 1][j] + 1);
            res = min(res, dp[i][j - 1] + 1);
            dp[i][j] = min(dp[i][j], res);
        }
    }

    cout << dp[n][m] << endl;
}