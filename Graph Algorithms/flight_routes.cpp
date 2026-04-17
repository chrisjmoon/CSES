#include <bits/stdc++.h>
using namespace std;

using pli = pair<long long, int>;

int main()
{
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<pli>> edges(n);
    for (int i = 0; i < m; i++)
    {
        int x, y;
        long long c;
        cin >> x >> y >> c;

        x--;
        y--;
        edges[x].push_back(pli(c, y));
    }

    vector<vector<long long>> dist(n);
    priority_queue<pli, vector<pli>, greater<pli>> pq;
    pq.push(pli(0, 0));
    while (dist[n - 1].size() < k)
    {
        long long cur_dist = pq.top().first;
        int node = pq.top().second;
        pq.pop();

        if (dist[node].size() >= k)
        {
            continue;
        }
        else
        {
            dist[node].push_back(cur_dist);
        }

        for (auto edge : edges[node])
        {
            long long next_dist = cur_dist + edge.first;
            int neighbor = edge.second;
            if (dist[neighbor].size() < k)
            {
                pq.push(pli(next_dist, neighbor));
            }
        }
    }

    for (int i = 0; i < k; i++)
    {
        cout << dist[n - 1][i] << " ";
    }
    cout << endl;
}