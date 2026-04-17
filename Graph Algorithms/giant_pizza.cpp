#include <bits/stdc++.h>
using namespace std;

int ng(int i)
{
    if (i % 2 == 0)
    {
        return i + 1;
    }
    else
    {
        return i - 1;
    }
}

void dfs1(int current, vector<bool> &seen, vector<vector<int>> &e, vector<int> &finish)
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
            dfs1(neighbor, seen, e, finish);
        }
    }

    finish.push_back(current);
}

void dfs2(int current, vector<bool> &seen, vector<vector<int>> &e, vector<int> &scc)
{
    seen[current] = true;
    for (auto neighbor : e[current])
    {
        if (!seen[neighbor])
        {
            scc[neighbor] = scc[current];
            dfs2(neighbor, seen, e, scc);
        }
    }
}

int main()
{
    int n, m;
    cin >> n >> m;

    vector<vector<int>> e(2 * m);
    vector<vector<int>> re(2 * m);
    for (int i = 0; i < n; i++)
    {
        int x, y;
        char s, t;
        cin >> s >> x >> t >> y;
        x--;
        y--;
        x *= 2;
        y *= 2;
        if (s == '-')
        {
            x += 1;
        }
        if (t == '-')
        {
            y += 1;
        }

        e[ng(y)].push_back(x);
        re[x].push_back(ng(y));
        e[ng(x)].push_back(y);
        re[y].push_back(ng(x));
    }

    vector<int> finish;
    vector<bool> seen(2 * m);
    // determine finish times
    for (int i = 0; i < 2 * m; i++)
    {
        if (!seen[i])
        {
            dfs1(i, seen, e, finish);
        }
    }

    vector<int> scc(2 * m, -1);
    int scc_count = 0;
    // traverse on the reverse graph in reverse finish order
    seen.assign(2 * m, false);
    for (int i = finish.size() - 1; i >= 0; i--)
    {
        if (scc[finish[i]] == -1)
        {
            scc_count++;
            scc[finish[i]] = scc_count;
            dfs2(finish[i], seen, re, scc);
        }
    }

    vector<char> res;
    for (int i = 0; i < m; i++)
    {
        int x = scc[2 * i];
        int y = scc[2 * i + 1];
        if (x == y)
        {
            cout << "IMPOSSIBLE" << endl;
            return 0;
        }

        if (x > y)
        {
            res.push_back('+');
        }
        else
        {
            res.push_back('-');
        }
    }

    for (auto v : res)
    {
        cout << v << " ";
    }
    cout << endl;
}