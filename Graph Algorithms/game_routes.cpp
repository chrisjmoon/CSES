#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> edges(n);
    vector<int> in_degree(n);
    for (int i = 0; i < m; i++)
    {
        int x, y;
        cin >> x >> y;
        x--;
        y--;
        edges[x].push_back(y);
        in_degree[y]++;
    }

    long long MOD = 1e9 + 7;
    vector<long long> dp(n);
    queue<int> q;
    dp[0] = 1;
    for (int i = 0; i < n; i++)
    {
        if (in_degree[i] == 0)
        {
            q.push(i);
        }
    }

    while (q.size())
    {
        int node = q.front();
        q.pop();

        for (auto neighbor : edges[node])
        {
            dp[neighbor] = (dp[neighbor] + dp[node]) % MOD;
            in_degree[neighbor]--;
            if (in_degree[neighbor] == 0)
            {
                q.push(neighbor);
            }
        }
    }

    cout << dp[n - 1] << endl;
}