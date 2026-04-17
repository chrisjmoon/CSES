#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, q;
    cin >> n >> q;
    vector<int> e(n);
    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        x--;
        e[i] = x;
    }

    vector<vector<int>> dp(32, vector<int>(n, -1));
    for (int i = 0; i < n; i++)
    {
        dp[0][i] = e[i];
    }

    for (int i = 1; i < 32; i++)
    {
        for (int j = 0; j < n; j++)
        {
            dp[i][j] = dp[i - 1][dp[i - 1][j]];
        }
    }

    for (int i = 0; i < q; i++)
    {
        int x, k;
        cin >> x >> k;
        x--;
        int node = x;
        for (int l = 0; l < 32; l++)
        {
            if ((1LL << l) & k)
            {
                node = dp[l][node];
            }
        }

        cout << node + 1 << '\n';
    }
}