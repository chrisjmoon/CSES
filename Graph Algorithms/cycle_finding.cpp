#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;

    long long MAX = 1e16;
    vector<vector<long long>> adj(n, vector<long long>(n, MAX));
    vector<pair<int, int>> edges;
    for (int i = 0; i < m; i++)
    {
        int x, y, z;
        cin >> x >> y >> z;
        x--;
        y--;
        adj[x][y] = min(adj[x][y], 1LL * z);
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (adj[i][j] != MAX)
            {
                edges.emplace_back(i, j);
            }
        }
    }

    // Bellman-Ford
    vector<long long> dp(n, 0);
    vector<int> parent(n);
    int last_updated_node = -1;
    for (int i = 0; i < n; i++)
    {
        last_updated_node = -1;
        for (auto edge : edges)
        {
            int x = edge.first;
            int y = edge.second;
            long long dist = dp[x] + adj[x][y];
            if (dist < dp[y])
            {
                dp[y] = dist;
                parent[y] = x;
                last_updated_node = y;
            }
        }
    }

    if (last_updated_node == -1)
    {
        cout << "NO" << endl;
    }
    else
    {
        vector<bool> seen(n);
        vector<int> history;
        int node = last_updated_node;
        while (!seen[node])
        {
            seen[node] = true;
            history.push_back(node);
            node = parent[node];
        }
        history.push_back(node);
        int node_index = find(history.begin(), history.end(), node) - history.begin();

        cout << "YES" << endl;
        for (int i = history.size() - 1; i >= node_index; i--)
        {
            cout << history[i] + 1 << " ";
        }
        cout << endl;
    }
}