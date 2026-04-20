#include <bits/stdc++.h>
using namespace std;

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

vector<pair<int, int>> prime_factorize(int n)
{
    vector<pair<int, int>> res;
    for (int p = 2; p * p <= n; p++)
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

vector<int> divisors(int n)
{
    vector<pair<int, int>> pf = prime_factorize(n);

    vector<int> d = {1};
    for (auto [prime, exp] : pf)
    {
        int sz = d.size();
        int p = 1;
        for (int i = 0; i < exp; i++)
        {
            p *= prime;
            for (int j = 0; j < sz; j++)
            {
                d.push_back(d[j] * p);
            }
        }
    }

    return d;
}

int main()
{
    for (auto v : divisors(18))
    {
        cout << v << " ";
    }
    cout << endl;
}