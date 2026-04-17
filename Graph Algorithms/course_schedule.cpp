#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;

    vector<vector<int>> edges(n);
    vector<int> in_count(n);
    for (int i = 0; i < m; i++)
    {
        int x, y;
        cin >> x >> y;
        x--;
        y--;
        edges[x].push_back(y);
        in_count[y]++;
    }

    // queue for nodes that are ready
    queue<int> start;
    for (int i = 0; i < n; i++)
    {
        if (in_count[i] == 0)
        {
            start.push(i);
        }
    }

    vector<int> res;
    while (start.size())
    {
        int node = start.front();
        start.pop();
        res.push_back(node);

        for (auto neighbor : edges[node])
        {
            in_count[neighbor]--;
            if (in_count[neighbor] == 0)
            {
                start.push(neighbor);
            }
        }
    }

    if (res.size() != n)
    {
        cout << "IMPOSSIBLE" << endl;
    }
    else
    {
        for (auto v : res)
        {
            cout << v + 1 << " ";
        }
        cout << endl;
    }
}