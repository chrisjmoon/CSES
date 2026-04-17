#include <bits/stdc++.h>
using namespace std;

// dfs to detect cycles
vector<int> dfs(int current, vector<vector<int>> &edges, vector<int> &seen, vector<int> &history)
{
    seen[current] = 1;
    for (auto neighbor : edges[current])
    {
        if (seen[neighbor] == 1)
        {
            history.push_back(neighbor);
            return history;
        }
        else if (seen[neighbor] == 0)
        {
            history.push_back(neighbor);
            vector<int> h = dfs(neighbor, edges, seen, history);
            if (h.size() != 0)
            {
                return h;
            }
            history.pop_back();
        }
    }
    seen[current] = 2;
    return vector<int>();
}

int main()
{
    int n, m;
    cin >> n >> m;

    vector<vector<int>> edges(n);
    for (int i = 0; i < m; i++)
    {
        int x, y;
        cin >> x >> y;
        x--;
        y--;
        edges[x].push_back(y);
    }

    vector<int> seen(n, 0); // 0: unseen, 1: on the stack, 2: finished exploring
    for (int i = 0; i < n; i++)
    {
        if (seen[i] == 0)
        {
            vector<int> history = {i};
            vector<int> h = dfs(i, edges, seen, history);
            if (h.size() != 0)
            {
                int index = find(h.begin(), h.end(), h.back()) - h.begin();
                cout << h.size() - index << endl;
                for (int j = index; j < h.size(); j++)
                {
                    cout << h[j] + 1 << " ";
                }
                cout << endl;
                return 0;
            }
        }
    }

    cout << "IMPOSSIBLE" << endl;
}