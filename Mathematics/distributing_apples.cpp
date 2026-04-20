#include <bits/stdc++.h>
using namespace std;

long long MOD = 1e9 + 7;

long long modpow(long long a, long long b)
{
    if (b == 0)
    {
        return 1;
    }

    long long res = 1;
    while (b > 0)
    {
        if (b & 1)
        {
            res = (res * a) % MOD;
            b -= 1;
        }

        a = (a * a) % MOD;
        b >>= 1;
    }

    return res;
}

int main()
{
    int n, m;
    cin >> n >> m;

    // stars and bars
    // m apples, n children
    // n - 1 bars
    // (m + n - 1 choose n - 1)

    vector<long long> f(m + n);
    f[0] = 1;
    for (int i = 1; i < m + n; i++)
    {
        f[i] = (i * f[i - 1]) % MOD;
    }

    long long inva = modpow(f[n - 1], MOD - 2);
    long long invb = modpow(f[m], MOD - 2);

    long long res = (f[m + n - 1] * inva) % MOD;
    res = (res * invb) % MOD;
    cout << res << endl;
}