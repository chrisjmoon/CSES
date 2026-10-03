#include <bits/stdc++.h>

using namespace std;

vector<vector<bool>> seen;
vector<string> grid;
vector<pair<int, int>> dir{{-1, 0}, {1, 0}, {0, 1}, {0, -1}};

void bfs(int x, int y)
{
    seen[x][y] = true;
    // x, y is the starting position
    deque<pair<int, int>> q{{x, y}};

    int n = seen.size();
    int m = seen[0].size();

    while (q.size())
    {
        auto [cx, cy] = q.front();
        q.pop_front();

        for (auto [dx, dy] : dir)
        {
            int nx{cx + dx};
            int ny{cy + dy};
            if (0 <= nx && nx < n && 0 <= ny && ny < m)
            {
                if (grid[nx][ny] == '.' && !seen[nx][ny])
                {
                    seen[nx][ny] = true;
                    q.emplace_back(nx, ny);
                }
            }
        }
    }
}

int main()
{
    int n, m;
    cin >> n >> m;

    grid.resize(n);
    for (int i = 0; i < n; i++)
    {
        cin >> grid[i];
    }

    int rooms{};

    // BFS
    // pair<int, int> represents our current position
    // a 2d seen vector represents visited positions

    seen.resize(n, vector<bool>(m));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (grid[i][j] == '.' && !seen[i][j])
            {
                bfs(i, j);
                rooms++;
            }
        }
    }

    cout << rooms << endl;
}