#include <bits/stdc++.h>
using namespace std;

long long MOD = 1e9 + 7;
long long PMOD = 1e9 + 6;
long long PPMOD = 500000002; // phi(phi(MOD))

long long phi(long long n)
{
    // prime factorize
    long long res = n;
    for (int p = 2; p * p <= n; p++)
    {
        if (n % p == 0)
        {
            while (n % p == 0)
            {
                n /= p;
            }
            res -= res / p;
        }
    }

    if (n > 1)
    {
        res -= res / n;
    }

    return res;
}

// b^c
long long exp(long long a, long long b, bool big_mod)
{
    if (b == 0)
    {
        return 1;
    }
    if (a == 0)
    {
        return 0;
    }
    if (b == 1)
    {
        return a;
    }

    long long mod = big_mod ? MOD : PMOD;
    b %= big_mod ? PMOD : PPMOD;

    long long res = exp(a, b / 2, big_mod);
    res = (res * res) % mod;

    if (b % 2)
    {
        res = (res * a) % mod;
    }

    return res;
}

long long solve(long long a, long long b, long long c)
{
    return exp(a, exp(b, c, false), true);
}

int main()
{
    int q;
    cin >> q;

    for (int i = 0; i < q; i++)
    {
        long long a, b, c;
        cin >> a >> b >> c;

        cout << solve(a, b, c) << endl;
    }
}