#include <bits/stdc++.h>
using namespace std;

using pint = pair<int, int>;
vector<pint> monsters;
vector<vector<int>> dist;
vector<vector<char>> path;
vector<pint> dir = {pint(0, 1), pint(0, -1), pint(1, 0), pint(-1, 0)};
string dir_str = "RLDU";
int n, m;

// can a slightly longer path avoid monsters?
// no - suppose a minimal path is interceptible
// with a longer path not interceptible; note that the distance
// of each cell to the destination must be less than that of the
// interceptible cell of the minimal path, hence, the path
// must be at most as long as the minimal path

void fill_distance(vector<string> &grid)
{
    queue<pint> q;
    int n = dist.size();
    int m = dist[0].size();
    vector<vector<bool>> seen(n, vector<bool>(m, false));
    for (auto p : monsters)
    {
        q.push(p);
        dist[p.first][p.second] = 0;
        seen[p.first][p.second] = true;
    }

    while (q.size())
    {
        pint p = q.front();
        q.pop();

        for (auto d : dir)
        {
            int i = p.first + d.first;
            int j = p.second + d.second;

            if (0 <= i && i < n && 0 <= j && j < m)
            {
                if (!seen[i][j] && grid[i][j] != '#')
                {
                    dist[i][j] = min(dist[i][j], dist[p.first][p.second] + 1);
                    seen[i][j] = true;
                    q.push(pint(i, j));
                }
            }
        }
    }
}

string bfs(int x, int y, vector<string> &grid)
{
    queue<pint> q;
    q.push(pint(x, y));
    vector<vector<bool>> seen(n, vector<bool>(m));
    seen[x][y] = true;
    while (q.size())
    {
        pint p = q.front();
        q.pop();

        int i = p.first;
        int j = p.second;

        // backtrack to find path if boundary
        if (i == 0 || i == n - 1 || j == 0 || j == m - 1)
        {
            vector<pint> path_history;
            string path_taken = "";
            while (i != x || j != y)
            {
                path_history.push_back(pint(i, j));
                path_taken += path[i][j];
                if (path[i][j] == 'U')
                {
                    i++;
                }
                else if (path[i][j] == 'D')
                {
                    i--;
                }
                else if (path[i][j] == 'R')
                {
                    j--;
                }
                else
                {
                    j++;
                }
            }
            path_history.push_back(pint(x, y));
            reverse(path_history.begin(), path_history.end());
            reverse(path_taken.begin(), path_taken.end());
            bool valid_path = true;

            for (int k = 0; k < path_history.size(); k++)
            {
                i = path_history[k].first;
                j = path_history[k].second;
                if (dist[i][j] <= k)
                {
                    valid_path = false;
                    break;
                }
            }

            if (valid_path)
            {
                return path_taken;
            }
        }

        for (int k = 0; k < 4; k++)
        {
            int ix = i + dir[k].first;
            int jy = j + dir[k].second;
            if (0 <= ix && ix < n && 0 <= jy && jy < m)
            {
                if (!seen[ix][jy] && grid[ix][jy] == '.')
                {
                    q.push(pint(ix, jy));
                    seen[ix][jy] = true;
                    path[ix][jy] = dir_str[k];
                }
            }
        }
    }

    return "NO";
}

int main()
{
    cin >> n >> m;
    vector<string> grid(n);
    for (int i = 0; i < n; i++)
    {
        cin >> grid[i];
    }

    int x, y;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (grid[i][j] == 'M')
            {
                monsters.push_back(pint(i, j));
            }
            if (grid[i][j] == 'A')
            {
                x = i;
                y = j;
            }
        }
    }

    dist.resize(n, vector<int>(m, 1e9));
    path.resize(n, vector<char>(m));
    fill_distance(grid);
    string path = bfs(x, y, grid);
    if (path != "NO")
    {
        cout << "YES" << endl;
        cout << path.size() << endl;
        if (path.size())
        {
            cout << path << endl;
        }
    }
    else
    {
        cout << "NO" << endl;
    }
}