#include <bits/stdc++.h>
using namespace std;

vector<int> finish;
vector<int> scc;
int scc_count = 0;

void dfs1(int current, vector<bool> &seen, vector<vector<int>> &e)
{
    if (seen[current])
    {
        return;
    }
    seen[current] = true;
    for (auto neighbor : e[current])
    {
        if (!seen[neighbor])
        {
            dfs1(neighbor, seen, e);
        }
    }
    finish.push_back(current);
}

void dfs2(int current, vector<bool> &seen, vector<vector<int>> &e)
{
    seen[current] = true;
    for (auto neighbor : e[current])
    {
        if (!seen[neighbor])
        {
            scc[neighbor] = scc[current];
            dfs2(neighbor, seen, e);
        }
    }
}

int main()
{
    int n, m;
    cin >> n >> m;

    vector<vector<int>> e(n);
    vector<vector<int>> re(n);
    scc.resize(n, -1);
    for (int i = 0; i < m; i++)
    {
        int x, y;
        cin >> x >> y;
        x--;
        y--;
        e[x].push_back(y);
        re[y].push_back(x);
    }

    // do DFS and record finish times
    vector<bool> seen(n);
    for (int i = 0; i < n; i++)
    {
        if (!seen[i])
        {
            dfs1(i, seen, e);
        }
    }
    // do DFS on reverse graph in order of decreasing finish times
    reverse(finish.begin(), finish.end());
    seen.assign(n, false);
    for (auto v : finish)
    {
        if (scc[v] == -1)
        {
            scc_count++;
            scc[v] = scc_count;
            dfs2(v, seen, re);
        }
    }

    cout << scc_count << endl;
    for (int i = 0; i < n; i++)
    {
        cout << scc[i] << " ";
    }
    cout << endl;
}