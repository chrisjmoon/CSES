#include <bits/stdc++.h>
using namespace std;

using pl = pair<long long, int>;
using pli = pair<pl, bool>;

int main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<pl>> e(n);
    for (int i = 0; i < m; i++)
    {
        int x, y, z;
        cin >> x >> y >> z;
        x--;
        y--;
        e[x].push_back(pl(z, y));
    }

    priority_queue<pli, vector<pli>, greater<pli>> pq;
    pq.push(pli(pl(0, 0), false));
    vector<vector<long long>> res(n, vector<long long>(2, 1e16));
    res[0][0] = 0;
    while (pq.size())
    {
        pli p = pq.top();
        pq.pop();
        long long price = p.first.first;
        int node = p.first.second;
        bool discount_taken = p.second;

        if (price > res[node][discount_taken])
        {
            continue;
        }

        for (auto neighbor_pair : e[node])
        {
            long long neighbor_price = neighbor_pair.first;
            int neighbor = neighbor_pair.second;
            if (discount_taken)
            {
                long long next_price = price + neighbor_price;
                if (next_price < res[neighbor][1])
                {
                    res[neighbor][1] = next_price;
                    pq.push(pli(pl(next_price, neighbor), discount_taken));
                }
            }
            else
            {
                long long next_price = price + neighbor_price;
                long long next_discount_price = price + neighbor_price / 2;
                if (next_price < res[neighbor][0])
                {
                    res[neighbor][0] = next_price;
                    pq.push(pli(pl(next_price, neighbor), false));
                }
                if (next_discount_price < res[neighbor][1])
                {
                    res[neighbor][1] = next_discount_price;
                    pq.push(pli(pl(next_discount_price, neighbor), true));
                }
            }
        }
    }

    cout << res[n - 1][1] << endl;
}