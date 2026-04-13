#include <bits/stdc++.h>
using namespace std;

void bfs(int x, vector<vector<int>> &e, vector<bool> &seen)
{
    queue<int> q;
    q.push(x);
    seen[x] = true;
    while (q.size())
    {
        int v = q.front();
        q.pop();

        for (auto neighbor : e[v])
        {
            if (!seen[neighbor])
            {
                q.push(neighbor);
                seen[neighbor] = true;
            }
        }
    }
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

    vector<bool> seen(n, false);
    vector<int> c;
    for (int i = 0; i < n; i++)
    {
        if (!seen[i])
        {
            c.push_back(i);
            bfs(i, e, seen);
        }
    }

    cout << c.size() - 1 << endl;
    for (int i = 0; i < c.size() - 1; i++)
    {
        cout << c[i] + 1 << " " << c[i + 1] + 1 << endl;
    }
}