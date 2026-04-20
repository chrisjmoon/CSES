#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

long long MOD = 1e9 + 7;
long long PHI = MOD - 1;

long long modpow(long long a, long long b, long long MOD)
{
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

int main()
{
    int n;
    cin >> n;

    long long N = 1;
    vector<pii> pf;
    for (int i = 0; i < n; i++)
    {
        int x, k;
        cin >> x >> k;
        pf.emplace_back(x, k);
        N = (N * modpow(x, k, MOD)) % MOD;
    }

    // number of divisors, sum of divisors, product of divisors
    long long num_mod = 1;
    long long num_pmod = 1;
    for (int i = 0; i < n; i++)
    {
        num_mod = (num_mod * (pf[i].second + 1)) % MOD;
        num_pmod = (num_pmod * (pf[i].second + 1)) % (MOD - 1);
    }

    // sum = \prod_p (p^{e + 1} - 1)/(p - 1)
    long long sum = 1;
    for (int i = 0; i < n; i++)
    {
        int prime = pf[i].first;
        int exp = pf[i].second;
        long long cur = (modpow(prime, exp + 1, MOD) - 1 + MOD) % MOD;
        cur = (cur * modpow(prime - 1, MOD - 2, MOD)) % MOD;
        sum = (sum * cur) % MOD;
    }

    // pair d and n/d
    // num divisors is odd when n is a square
    long long prod = 1;
    long long count = 1;

    for (int i = 0; i < n; i++)
    {
        long long prime = pf[i].first;
        long long exp = pf[i].second;
        // (prod, prod * p, prod * p^2, ..., prod * p^exp)
        // prod = prod^(exp + 1) * (p^((exp + 1)*exp/2))^cnt
        long long tri = ((exp + 1) * exp) / 2 % PHI;
        prod = (modpow(prod, exp + 1, MOD) * modpow(modpow(prime, tri, MOD), count, MOD)) % MOD;
        count = (count * (exp + 1)) % PHI;
    }

    cout << num_mod << " " << sum << " " << prod << endl;
}