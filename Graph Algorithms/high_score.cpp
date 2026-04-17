#include <bits/stdc++.h>
using namespace std;

using pint = pair<int, int>;
int main()
{
    int n, m;
    cin >> n >> m;

    long long MIN = -1e16;
    long long MAX = 1e16;
    vector<vector<long long>> adj(n, vector<long long>(n, MIN));
    vector<pint> edges;
    for (int i = 0; i < m; i++)
    {
        int x, y;
        long long z;
        cin >> x >> y >> z;
        x--;
        y--;
        edges.emplace_back(x, y);
        adj[x][y] = max(adj[x][y], z);
    }

    // Relaxation
    vector<long long> dp(n, MIN);
    dp[0] = max(1LL * 0, adj[0][0]); // use a self loop on the first node if it exists
    for (int i = 0; i < n - 1; i++)
    {
        for (auto e : edges)
        {
            if (dp[e.first] != MIN)
            {
                dp[e.second] = max(dp[e.second], dp[e.first] + adj[e.first][e.second]);
            }
        }
    }

    long long res = dp[n - 1];

    // do another batch to account for loops
    for (int i = 0; i < n; i++)
    {
        for (auto e : edges)
        {
            // spread infection
            if (dp[e.first] == MAX)
            {
                dp[e.second] = MAX;
            }
            else if (dp[e.first] != MIN)
            {
                // hit a positive loop -> start infection
                if ((dp[e.first] + adj[e.first][e.second]) > dp[e.second])
                {
                    dp[e.second] = MAX;
                }
            }
        }
    }

    cout << ((dp[n - 1] == MAX) ? -1 : dp[n - 1]) << endl;
}