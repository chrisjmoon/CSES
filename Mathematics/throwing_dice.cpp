#include <bits/stdc++.h>
using namespace std;

using ll = long long;
ll MOD = 1e9 + 7;

vector<vector<ll>> mult(vector<vector<ll>> &a, vector<vector<ll>> &b)
{
    vector<vector<ll>> res(6, vector<ll>(6));

    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            long long c = 0;
            for (int k = 0; k < 6; k++)
            {
                c = (c + a[i][k] * b[k][j]) % MOD;
            }
            res[i][j] = c;
        }
    }

    return res;
}

int main()
{
    ll n;
    cin >> n;

    vector<vector<ll>> res(6, vector<ll>(6));
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            res[i][j] = pow(2, max(5 - i - j, 0));
        }
    }
    vector<vector<ll>> base(6, vector<ll>(6));
    for (int i = 0; i < 6; i++)
    {
        base[0][i] = 1;
    }
    for (int i = 1; i < 6; i++)
    {
        base[i][i - 1] = 1;
    }

    // let T be the transition matrix
    // T^k * res => 6 + k

    if (n < 6)
    {
        cout << res[0][6 - n] << endl;
        return 0;
    }

    n -= 6;
    while (n > 0)
    {
        if (n & 1)
        {
            res = mult(base, res);
            n -= 1;
        }

        base = mult(base, base);
        n >>= 1;
    }

    cout << res[0][0] << endl;
}