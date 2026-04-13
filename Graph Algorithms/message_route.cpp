#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> e(n);
    for (int i = 0; i < m; i++)
    {
        int x, y;
        cin >> x >> y;
        x--;
        y--;
        e[x].push_back(y);
        e[y].push_back(x);
    }

    vector<int> path_history(n);
    vector<bool> seen(n);
    queue<int> q;
    q.push(0);
    seen[0] = true;
    while (q.size())
    {
        int v = q.front();
        q.pop();

        for (auto neighbor : e[v])
        {
            if (!seen[neighbor])
            {
                seen[neighbor] = true;
                q.push(neighbor);
                path_history[neighbor] = v;
            }
        }
    }

    if (!seen[n - 1])
    {
        cout << "IMPOSSIBLE" << endl;
    }
    else
    {
        vector<int> path;
        int v = n - 1;
        while (v != 0)
        {
            path.push_back(v);
            v = path_history[v];
        }
        path.push_back(0);
        reverse(path.begin(), path.end());
        cout << path.size() << endl;
        for (auto v : path)
        {
            cout << v + 1 << " ";
        }
        cout << endl;
    }
}