#include <bits/stdc++.h>
using namespace std;

using pint = pair<int, int>;

void bfs(int x, int y, vector<string> &grid, vector<vector<bool>> &seen)
{
    static vector<pint> dir = {pint(-1, 0), pint(1, 0), pint(0, 1), pint(0, -1)};
    queue<pint> q;
    q.push(pint(x, y));
    int n = grid.size();
    int m = grid[0].size();
    seen[x][y] = true;
    while (q.size())
    {
        pint p = q.front();
        q.pop();
        int i = p.first;
        int j = p.second;
        for (auto d : dir)
        {
            int dx = d.first;
            int dy = d.second;
            if (0 <= i + dx && i + dx < n && 0 <= j + dy && j + dy < m)
            {
                if (grid[i + dx][j + dy] == '.' && !seen[i + dx][j + dy])
                {
                    q.push(pint(i + dx, j + dy));
                    seen[i + dx][j + dy] = true;
                }
            }
        }
    }
}

int main()
{
    int n, m;
    cin >> n >> m;
    vector<string> grid(n);
    for (int i = 0; i < n; i++)
    {
        cin >> grid[i];
    }

    int res = 0;
    vector<vector<bool>> seen(n, vector<bool>(m));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (grid[i][j] == '.' && !seen[i][j])
            {
                bfs(i, j, grid, seen);
                res++;
            }
        }
    }

    cout << res << endl;
}