#include <bits/stdc++.h>
using namespace std;

long long MOD = 1e9 + 7;

vector<pair<long long, int>> prime_factorize(long long n)
{
    vector<pair<long long, int>> res;
    for (long long p = 2; p * p <= n; p++)
    {
        if (n % p != 0)
        {
            continue;
        }
        int exp = 0;
        while (n % p == 0)
        {
            exp++;
            n /= p;
        }
        res.emplace_back(p, exp);
    }

    if (n > 1)
    {
        res.emplace_back(n, 1);
    }

    return res;
}

long long modpow(long long a, long long e, long long mod)
{
    long long res = 1;
    while (e)
    {
        if (e & 1)
            res = res * a % mod;
        a = a * a % mod;
        e >>= 1;
    }
    return res;
}

// each divisor contributes floor(n / d)
// floor(n / 1), floor(n / 2), floor(n / 3), floor(n / 4), ...
// floor(n / (floor(n / 2) + 1))
int main()
{
    long long n;
    cin >> n;

    long long l = 1;
    long long res = 0;
    while (l <= n)
    {
        long long q = n / l;
        long long r = n / q;
        // range [d, floor(n / q)]
        // l * floor(n / l) + ... + r * floor(n / r)
        long long a = (r + l);
        long long b = (r - l + 1);
        if (a % 2 == 0)
        {
            a /= 2;
        }
        else
        {
            b /= 2;
        }
        long long s = (a % MOD) * (b % MOD) % MOD;
        s = (s * q) % MOD;
        res = (res + s) % MOD;
        l = r + 1;
    }

    cout << res << endl;
}