#include <bits/stdc++.h>

using namespace std;

vector<int> subordinates;
vector<vector<int>> edges;

void dfs(int c)
{
    for (auto worker : edges[c])
    {
        dfs(worker);
        subordinates[c] += (subordinates[worker] + 1);
    }
}

int main()
{
    int n;
    cin >> n;

    subordinates.resize(n, 0);
    edges.resize(n);

    for (int i = 0; i < n - 1; i++)
    {
        int b;
        cin >> b;
        b--;

        edges[b].push_back(i + 1);
    }

    dfs(0);

    for (int i = 0; i < n; i++)
    {
        cout << subordinates[i] << " ";
    }
    cout << endl;
}