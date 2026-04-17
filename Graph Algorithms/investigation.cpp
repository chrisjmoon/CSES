#include <bits/stdc++.h>
using namespace std;
using pl = pair<long long, int>;

int main()
{
    int n, m;
    cin >> n >> m;

    vector<vector<pair<long, int>>> edges(n);
    for (int i = 0; i < m; i++)
    {
        int x, y;
        long long z;
        cin >> x >> y >> z;
        x--;
        y--;
        edges[x].push_back(pair<int, int>(z, y));
    }

    long long MOD = 1e9 + 7;
    long long MAX = 1e16;
    vector<vector<long long>> dp(4);
    dp[0] = vector<long long>(n, MAX); // price
    dp[1] = vector<long long>(n, MAX); // min flights
    dp[2] = vector<long long>(n, 0);   // max flights
    dp[3] = vector<long long>(n, 0);   // paths
    dp[0][0] = 0;
    dp[1][0] = 0;
    dp[2][0] = 0;
    dp[3][0] = 1;

    priority_queue<pl, vector<pl>, greater<pl>> pq;
    pq.push(pl(0, 0));
    while (pq.size())
    {
        long long price = pq.top().first;
        int node = pq.top().second;
        pq.pop();

        if (price > dp[0][node])
        {
            continue;
        }

        for (auto neighbor : edges[node])
        {
            long long next_price = price + neighbor.first;
            int next_node = neighbor.second;
            if (next_price < dp[0][next_node])
            {
                dp[0][next_node] = next_price;
                dp[1][next_node] = dp[1][node] + 1;
                dp[2][next_node] = dp[2][node] + 1;
                dp[3][next_node] = dp[3][node];
                pq.push(pl(next_price, next_node));
            }
            else if (next_price == dp[0][next_node])
            {
                dp[1][next_node] = min(dp[1][next_node], dp[1][node] + 1);
                dp[2][next_node] = max(dp[2][next_node], dp[2][node] + 1);
                dp[3][next_node] = (dp[3][next_node] + dp[3][node]) % MOD;
            }
            else
            {
                continue;
            }
        }
    }

    // minimum price, number of paths with minimum price, min flights in path, max flights in path
    cout << dp[0][n - 1] << " " << dp[3][n - 1] << " " << dp[1][n - 1] << " " << dp[2][n - 1]
         << endl;
}