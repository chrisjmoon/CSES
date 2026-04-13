#include <bits/stdc++.h>
using namespace std;

bool bfs(int x, vector<int> &color, vector<vector<int>> &e)
{
    queue<int> q;
    q.push(x);
    color[x] = 1;

    while (q.size())
    {
        int v = q.front();
        q.pop();

        for (auto neighbor : e[v])
        {
            if (color[neighbor] != 0 && (color[v] == color[neighbor]))
            {
                return false;
            }
            if (color[neighbor] == 0)
            {
                q.push(neighbor);
                color[neighbor] = color[v] == 1 ? 2 : 1;
            }
        }
    }

    return true;
}

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

    vector<int> color(n);
    for (int i = 0; i < n; i++)
    {
        if (color[i] == 0 && !bfs(i, color, e))
        {
            cout << "IMPOSSIBLE" << endl;
            return 0;
        }
    }

    for (int i = 0; i < n; i++)
    {
        cout << color[i] << " ";
    }
    cout << endl;
}