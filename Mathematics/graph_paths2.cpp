#include <bits/stdc++.h>
using namespace std;

using ll = long long;
ll MOD = 1e9 + 7;
vector<vector<ll>> adj;

vector<vector<ll>> operate(vector<vector<ll>> &a, vector<vector<ll>> &b)
{
    int n = a.size();
    vector<vector<ll>> res(n, vector<ll>(n));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (b[i][j] == 0)
            {
                continue;
            }

            for (int k = 0; k < n; k++)
            {
                // k -> i -> j
                if (a[k][i] == 0)
                {
                    continue;
                }
                if (res[k][j] == 0)
                {
                    res[k][j] = (a[k][i] + b[i][j]);
                }
                else
                {
                    res[k][j] = min(res[k][j], (a[k][i] + b[i][j]));
                }
            }
        }
    }

    return res;
}

int main()
{
    int n, m;
    long long k;
    cin >> n >> m >> k;

    adj.resize(n, vector<ll>(n, 0));
    for (int i = 0; i < m; i++)
    {
        int x, y;
        long long w;
        cin >> x >> y >> w;
        x--;
        y--;

        if (adj[x][y] == 0)
        {
            adj[x][y] = w;
        }
        else
        {
            adj[x][y] = min(adj[x][y], w);
        }
    }

    vector<vector<ll>> res = adj;
    vector<vector<ll>> base = adj;
    k -= 1;
    while (k > 0)
    {

        if (k & 1)
        {
            res = operate(base, res);
            k -= 1;
        }

        base = operate(base, base);
        k >>= 1;
    }

    cout << (res[0][n - 1] != 0 ? res[0][n - 1] : -1) << endl;
}