#include <bits/stdc++.h>
using namespace std;

void dfs(int current, vector<vector<int>> &e, vector<bool> &seen, vector<bool> &reachable)
{
    reachable[current] = true;
    seen[current] = true;
    for (auto neighbor : e[current])
    {
        if (!seen[neighbor])
        {
            dfs(neighbor, e, seen, reachable);
        }
    }
}

int main()
{
    int n, m;
    cin >> n >> m;

    vector<vector<int>> e(n);
    vector<vector<int>> re(n);
    for (int i = 0; i < m; i++)
    {
        int x, y;
        cin >> x >> y;
        x--;
        y--;
        e[x].push_back(y);
        re[y].push_back(x);
    }

    // run DFS on 0
    vector<bool> reachable(n);
    vector<bool> seen(n);
    dfs(0, e, seen, reachable);

    // run DFS on 0 with reversed edges
    vector<bool> reverse_reachable(n);
    seen.assign(n, false);
    dfs(0, re, seen, reverse_reachable);

    for (int i = 0; i < n; i++)
    {
        if (!reachable[i])
        {
            cout << "NO" << endl;
            cout << 1 << " " << i + 1 << endl;
            return 0;
        }
        else if (!reverse_reachable[i])
        {
            cout << "NO" << endl;
            cout << i + 1 << " " << 1 << endl;
            return 0;
        }
    }

    cout << "YES" << endl;
}