#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, m, q;
    cin >> n >> m >> q;
    vector<vector<long long>> adj(n, vector<long long>(n, 0));
    for (int i = 0; i < m; i++)
    {
        int x, y;
        long long z;
        cin >> x >> y >> z;
        x--;
        y--;
        if (adj[x][y] != 0)
        {
            adj[x][y] = min(adj[x][y], z);
            adj[y][x] = adj[x][y];
        }
        else
        {
            adj[x][y] = z;
            adj[y][x] = z;
        }
    }

    // Floyd-Warshall
    long long MAX = 1e18;
    vector<vector<long long>> dp(n, vector<long long>(n, MAX));
    for (int i = 0; i < n; i++)
    {
        dp[i][i] = 0;
        for (int j = 0; j < n; j++)
        {
            if (i == j)
            {
                continue;
            }
            if (adj[i][j] != 0)
            {
                dp[i][j] = adj[i][j];
            }
        }
    }
    for (int i = 0; i < n; i++) // introducing node i
    {
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < n; k++)
            {
                dp[j][k] = min(dp[j][k], dp[i][k] + dp[j][i]);
            }
        }
    }

    for (int i = 0; i < q; i++)
    {
        int x, y;
        cin >> x >> y;
        x--;
        y--;
        if (dp[x][y] == MAX)
        {
            cout << -1 << '\n';
        }
        else
        {
            cout << dp[x][y] << '\n';
        }
    }
}