#include <bits/stdc++.h>
using namespace std;

// determine if x is part of a loop
int dfs(int x, vector<vector<int>> &e, vector<int> &path_history, vector<bool> &seen)
{
    stack<int> s;
    s.push(x);
    while (s.size())
    {
        int v = s.top();
        s.pop();
        if (seen[v])
        {
            continue;
        }
        seen[v] = true;

        for (int neighbor : e[v])
        {
            if (seen[neighbor] && path_history[v] != neighbor)
            {
                path_history[neighbor] = v;
                return neighbor;
            }

            if (!seen[neighbor])
            {
                s.push(neighbor);
                path_history[neighbor] = v;
            }
        }
    }

    return -1;
}

int main()
{
    int n, m;
    cin >> n >> m;

    vector<vector<int>> e(n);
    vector<int> path_history(n, -1);
    vector<bool> seen(n);
    for (int i = 0; i < m; i++)
    {
        int x, y;
        cin >> x >> y;
        x--;
        y--;
        e[x].push_back(y);
        e[y].push_back(x);
    }

    for (int i = 0; i < n; i++)
    {
        if (!seen[i])
        {
            int v = dfs(i, e, path_history, seen);
            if (v == -1)
                continue;
            vector<int> path = {v};
            int w = path_history[v];
            while (w != v)
            {
                path.push_back(w);
                w = path_history[w];
            }
            path.push_back(v);
            cout << path.size() << endl;
            for (int v : path)
            {
                cout << v + 1 << " ";
            }
            cout << endl;
            return 0;
        }
    }

    cout << "IMPOSSIBLE" << endl;
}