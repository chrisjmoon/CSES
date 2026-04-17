#include <bits/stdc++.h>
using namespace std;

using pli = pair<long long, int>;

int main()
{
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> edges;
    priority_queue<pli, vector<pli>, greater<pli>> pq;
    for (int i = 0; i < m; i++)
    {
        int x, y;
        int z;
        cin >> x >> y >> z;
        x--;
        y--;
        edges.emplace_back(x, y);
        pq.push(pli(z, i));
    }

    vector<int> id(n);
    for (int i = 0; i < n; i++)
    {
        id[i] = i;
    }

    long long res = 0;
    while (pq.size())
    {
        long long cost = pq.top().first;
        int e = pq.top().second;
        pq.pop();

        int x = edges[e].first;
        int y = edges[e].second;
        int cx = id[x];
        int cy = id[y];
        while (cx != id[cx])
        {
            cx = id[cx];
        }
        while (cy != id[cy])
        {
            cy = id[cy];
        }

        if (cx == cy) // already in the same component
        {
            continue;
        }

        res += cost;
        if (cx > cy)
        {
            swap(cx, cy);
        }
        id[cy] = cx;
    }

    for (int i = 0; i < n; i++)
    {
        int ci = id[i];
        while (ci != id[ci])
        {
            ci = id[ci];
        }
        if (ci != 0)
        {
            cout << "IMPOSSIBLE" << endl;
            return 0;
        }
    }

    cout << res << endl;
}