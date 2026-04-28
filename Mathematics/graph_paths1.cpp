#include <bits/stdc++.h>
using namespace std;

using ll = long;

ll MOD = 1e9 + 7;

vector<vector<ll>> mult(const vector<vector<ll>> &a, const vector<vector<ll>> &b)
{
    int n = a.size();

    vector<vector<ll>> res(n, vector<ll>(n));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            // add contribution of a[i][j]
            if (a[i][j] == 0)
            {
                continue;
            }

            for (int k = 0; k < n; k++)
            {
                res[i][k] = (res[i][k] + a[i][j] * b[j][k]) % MOD;
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

    vector<vector<ll>> base(n, vector<ll>(n, 0));

    for (int i = 0; i < m; i++)
    {
        int x, y;
        cin >> x >> y;
        x--;
        y--;
        base[x][y] = (base[x][y] + 1) % MOD;
    }

    // adj^k
    vector<vector<ll>> res(n, vector<ll>(n));
    for (int i = 0; i < n; i++)
    {
        res[i][i] = 1;
    }
    while (k > 0)
    {
        if (k & 1)
        {
            res = move(mult(res, base));
            k -= 1;
        }

        base = move(mult(base, base));
        k >>= 1;
    }

    cout << res[0][n - 1] << endl;
}