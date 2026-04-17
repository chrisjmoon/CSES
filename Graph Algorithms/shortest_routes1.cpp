#include <bits/stdc++.h>
using namespace std;

using pli = pair<long long, int>;
using pq = priority_queue<pli, vector<pli>, greater<pli>>;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;

    vector<vector<pair<int, int>>> adj(n);
    for (int i = 0; i < m; i++)
    {
        int x, y, z;
        cin >> x >> y >> z;
        x--;
        y--;
        adj[x].push_back(pair<int, int>(z, y));
    }

    pq q; // push top pop
    vector<long long> res(n, 1e16);
    res[0] = 0;
    q.push(pli(0, 0));

    while (q.size())
    {
        auto [distance, node] = q.top();
        q.pop();

        if (distance > res[node])
            continue;

        for (auto p : adj[node])
        {
            if ((distance + p.first) < res[p.second])
            {
                res[p.second] = distance + p.first;
                q.push(pli(distance + p.first, p.second));
            }
        }
    }

    for (auto d : res)
    {
        cout << d << " ";
    }
    cout << endl;
}