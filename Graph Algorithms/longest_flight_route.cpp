#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

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

    queue<int> q;
    long long MIN = -1e16;
    vector<long long> dp(n, MIN);
    vector<int> parent(n);

    dp[0] = 0;
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
            // cout << "node, neighbor: " << node + 1 << " " << neighbor + 1 << endl;
            // cout << "1 + dp[node]: " << 1 + dp[node] << endl;
            if ((1 + dp[node]) > dp[neighbor])
            {
                dp[neighbor] = 1 + dp[node];
                parent[neighbor] = node;
            }
            in_degree[neighbor]--;
            if (in_degree[neighbor] == 0)
            {
                q.push(neighbor);
            }
        }
    }

    if (dp[n - 1] <= 0)
    {
        cout << "IMPOSSIBLE" << endl;
    }
    else
    {
        int node = n - 1;
        vector<int> res;
        while (node != 0)
        {
            res.push_back(node);
            node = parent[node];
        }
        res.push_back(0);
        reverse(res.begin(), res.end());
        cout << res.size() << endl;
        for (auto v : res)
        {
            cout << v + 1 << " ";
        }
        cout << endl;
    }
}