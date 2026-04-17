#include <bits/stdc++.h>
using namespace std;

void dfs1(int current, vector<bool> &seen, vector<vector<int>> &e, vector<int> &finish)
{
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

    vector<long long> c(n);
    for (int i = 0; i < n; i++)
    {
        cin >> c[i];
    }

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

    // determine SCC
    vector<bool> seen(n);
    vector<int> finish;
    for (int i = 0; i < n; i++)
    {
        if (!seen[i])
        {
            dfs1(i, seen, e, finish);
        }
    }

    vector<int> scc(n, -1);
    seen.assign(n, false);
    int scc_count = 0;
    reverse(finish.begin(), finish.end());
    for (auto v : finish)
    {
        if (scc[v] == -1)
        {
            scc[v] = scc_count;
            dfs2(v, seen, re, scc);
            scc_count++;
        }
    }

    // fill in dp in reverse topological order
    vector<long long> sdp(scc_count);
    vector<long long> dp(scc_count);
    reverse(finish.begin(), finish.end());
    for (int i = 0; i < n; i++)
    {
        sdp[scc[i]] += c[i];
        dp[scc[i]] = sdp[scc[i]];
    }
    for (auto v : finish)
    {
        for (auto neighbor : e[v])
        {
            if (scc[v] < scc[neighbor])
            {
                dp[scc[v]] = max(sdp[scc[v]] + dp[scc[neighbor]], dp[scc[v]]);
            }
        }
    }

    cout << *max_element(dp.begin(), dp.end()) << endl;
}