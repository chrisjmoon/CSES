#include <bits/stdc++.h>
using namespace std;

// take available edge
// if neighbor has already been explored, use suffix history to piece together path
//

int n, m;

vector<vector<pair<int, int>>> e;
vector<int> seen;                // 0: not touched, 1: in the stack, 2: done exploring
vector<vector<bitset<1000>>> eh; // paths leading from i to n
vector<vector<vector<int>>> ph;

// if the nodes
vector<vector<int>> dfs(int c, bitset<1000> &edges, vector<int> &path)
{
    seen[c] = 1;
    if (c == e.size() - 1)
    {
        seen[c] = 2;
        return vector<vector<int>>{{c}};
    }

    path.push_back(c);
    vector<vector<int>> res;
    for (int i = 0; i < e[c].size(); i++)
    {
        int v = e[c][i].first;
        int edge_id = e[c][i].second;
        if (!seen[v] && !edges[edge_id]) // neighbor untouched
        {
            edges[edge_id] = true;
            dfs(v, edges, path);
            edges[edge_id] = false;
        }
        elif (seen[v] == 2)
        {
            for (int j = 0; j < eh[v].size(); j++)
            {
            }
        }
    }
    seen[c] = 2;
    path.pop_back();
    return res;
}

int main()
{
    cin >> n >> m;

    adj.resize(n, vector<bool>(n));
    e.resize(n);
    seen.resize(n);
    eh.resize(n);
    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;

        a--;
        b--;
        e[a].emplace_back(b, i);
    }

    vector<vector<int>> res = dfs(0);
    cout << res.size() << endl;
    for (auto v : res)
    {
        cout << v.size() << endl;
        for (auto it = v.rbegin(); it != v.rend(); it++)
        {
            cout << *it + 1 << " ";
        }
        cout << endl;
    }
}