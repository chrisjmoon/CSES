#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

void walk(int current, vector<bool> &eu, vector<int> &ep, vector<vector<pii>> &e, vector<int> &path)
{

    while (ep[current] < e[current].size())
    {
        pii edge = e[current][ep[current]];
        ep[current]++;
        int neighbor = edge.first;
        int edge_id = edge.second;
        if (eu[edge_id])
        {
            continue;
        }
        else
        {
            eu[edge_id] = true;
            walk(neighbor, eu, ep, e, path);
        }
    }

    // add to path now that all edges have been used up
    path.push_back(current);
}

int main()
{
    int n, m;
    cin >> n >> m;

    vector<vector<pii>> e(n);
    vector<int> ep(n);
    vector<int> deg(n);
    int edge_count = 0;
    for (int i = 0; i < m; i++)
    {
        int x, y;
        cin >> x >> y;
        x--;
        y--;
        e[x].emplace_back(y, edge_count);
        e[y].emplace_back(x, edge_count);
        deg[x]++;
        deg[y]++;
        edge_count++;
    }

    for (int i = 0; i < n; i++)
    {
        if (deg[i] % 2)
        {
            cout << "IMPOSSIBLE" << endl;
            return 0;
        }
    }

    vector<bool> eu(edge_count);
    vector<int> path;
    walk(0, eu, ep, e, path);

    for (int i = 0; i < edge_count; i++)
    {
        if (!eu[i])
        {
            cout << "IMPOSSIBLE" << endl;
            return 0;
        }
    }

    reverse(path.begin(), path.end());
    for (auto v : path)
    {
        cout << v + 1 << " ";
    }
    cout << endl;
}