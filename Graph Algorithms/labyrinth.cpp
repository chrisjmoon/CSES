#include <bits/stdc++.h>
using namespace std;

using pint = pair<int, int>;

string bfs(int x, int y, vector<string> &grid)
{
    static vector<pint> dir = {pint(0, 1), pint(0, -1), pint(1, 0), pint(-1, 0)};
    static string dir_char = "RLDU";
    int n = grid.size();
    int m = grid[0].size();
    vector<vector<bool>> seen(n, vector<bool>(m));
    vector<vector<char>> path_history(n, vector<char>(m));
    seen[x][y] = true;
    queue<pint> q;
    q.push(pint(x, y));

    while (!q.empty())
    {
        pint p = q.front();
        q.pop();
        for (int k = 0; k < 4; k++)
        {
            int i = p.first + dir[k].first;
            int j = p.second + dir[k].second;
            if (0 <= i && i < n && 0 <= j && j < m)
            {
                if (grid[i][j] == 'B')
                {
                    string total_path;
                    path_history[i][j] = dir_char[k];
                    while (grid[i][j] != 'A')
                    {
                        total_path.push_back(path_history[i][j]);
                        if (path_history[i][j] == 'R')
                        {
                            j--;
                        }
                        else if (path_history[i][j] == 'L')
                        {
                            j++;
                        }
                        else if (path_history[i][j] == 'U')
                        {
                            i++;
                        }
                        else
                        {
                            i--;
                        }
                    }
                    reverse(total_path.begin(), total_path.end());
                    return total_path;
                }
                if (grid[i][j] == '.' && !seen[i][j])
                {
                    q.push(pint(i, j));
                    seen[i][j] = true;
                    path_history[i][j] = dir_char[k];
                }
            }
        }
    }

    return "";
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

    vector<vector<bool>> seen(n, vector<bool>(m));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (grid[i][j] == 'A')
            {
                string total_path = bfs(i, j, grid);
                if (total_path != "")
                {
                    cout << "YES" << endl;
                    cout << total_path.size() << endl;
                    cout << total_path << endl;
                    return 0;
                }
            }
        }
    }

    cout << "NO" << endl;
}