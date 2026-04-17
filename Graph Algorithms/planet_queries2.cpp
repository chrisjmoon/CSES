#include <bits/stdc++.h>
using namespace std;

void dfs(int current, vector<int> &pos, vector<int> &dtc, vector<int> &cyl, vector<int> &cyi,
         vector<int> &cye, vector<bool> &seen, vector<int> &edge, vector<int> &path)
{
    seen[current] = true;
    path.push_back(current);
    int neighbor = edge[current];
    if (seen[neighbor])
    {
        int index = find(path.begin(), path.end(), neighbor) - path.begin();
        if (index != path.size()) // cycle detected
        {
            int cycle_length = path.size() - index;
            int cycle_id = cyl.size();
            cyl.push_back(cycle_length);
            for (int i = index; i < path.size(); i++) // cycle nodes
            {
                pos[path[i]] = i - index;
                cyi[path[i]] = cycle_id;
            }
            for (int i = 0; i < index; i++) // nodes leading into but outside cycle
            {
                dtc[path[i]] = index - i;
                cye[path[i]] = neighbor;
                cyi[path[i]] = cycle_id;
            }
        }
        else // entering cycle
        {
            if (dtc[neighbor] != -1) // neighbor is outside of explored cycle
            {
                dtc[current] = dtc[neighbor] + 1;
                cye[current] = cye[neighbor];
                cyi[current] = cyi[neighbor];
            }
            else // neighbor is part of explored cycle
            {
                dtc[current] = 1;
                cye[current] = neighbor;
                cyi[current] = cyi[neighbor];
            }
        }
    }
    else
    {
        dfs(neighbor, pos, dtc, cyl, cyi, cye, seen, edge, path);
    }
}

int main()
{

    int n, q;
    cin >> n >> q;

    vector<int> edge(n);
    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        x--;
        edge[i] = x;
    }

    // for each node of the cycle, we can determine it's index along the cycle
    // 1 -> 2 -> 3 -> 4 -> 1, pos[1] = 0, pos[2] = 1, pos[3] = 2, ...
    // for nodes outside the cycle, we calculate the distance from the node to its nearest cycle
    vector<int> pos(n, -1); // index along cycle
    vector<int> dtc(n, -1); // distance to cycle
    vector<int> cyl;        // cycle length
    vector<int> cye(n, -1); // cycle entrance
    vector<int> cyi(n, -1); // cycle id
    vector<bool> seen(n, false);
    // (node outside cycle, node outside cycle) dtc - dtc
    // (node outside cycle, node inside cycle) dtc + pos
    // (node inside cycle, node inside cycle) pos - pos OR L - (pos - pos)

    for (int i = 0; i < n; i++)
    {
        if (!seen[i])
        {
            vector<int> path;
            dfs(i, pos, dtc, cyl, cyi, cye, seen, edge, path);
        }
    }

    vector<vector<int>> dp(32, vector<int>(n, -1));
    for (int i = 0; i < n; i++)
    {
        dp[0][i] = edge[i];
    }
    for (int i = 1; i < 32; i++)
    {
        for (int j = 0; j < n; j++)
        {
            dp[i][j] = dp[i - 1][dp[i - 1][j]];
        }
    }

    vector<int> res;
    for (int i = 0; i < q; i++)
    {
        int x, y;
        cin >> x >> y;
        x--;
        y--;

        if (cyi[x] != cyi[y]) // different cycle ids
        {
            res.push_back(-1);
            continue;
        }

        if (dtc[x] != -1 && dtc[y] != -1) // both outside the cycle
        {
            if (cye[x] != cye[y] || dtc[y] > dtc[x])
            {
                res.push_back(-1);
                continue;
            }

            int gap = dtc[x] - dtc[y];
            for (int j = 0; j < 32; j++)
            {
                if ((1 << j) & gap)
                {
                    x = dp[j][x];
                }
            }
            if (x != y)
            {
                res.push_back(-1);
            }
            else
            {
                res.push_back(gap);
            }
        }
        else if (dtc[x] != -1 && dtc[y] == -1) // x is outside, y is inside
        {
            res.push_back(dtc[x] + pos[y]);
        }
        else // both inside the cycle
        {
            int e = pos[x];
            int f = pos[y];
            int cycle_length = cyl[cyi[x]];
            if (f >= e)
            {
                res.push_back(f - e);
            }
            else
            {
                res.push_back(cycle_length + (f - e));
            }
        }
    }

    for (auto v : res)
    {
        cout << v << endl;
    }
}