#include <bits/stdc++.h>
using namespace std;

long long MOD = 1e9 + 7;

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

int main()
{
    int n;
    cin >> n;
    vector<int> p(n);
    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        x--;
        p[i] = x;
    }

    vector<int> cycle_lengths;
    vector<int> seen(n);
    for (int i = 0; i < n; i++)
    {
        if (!seen[i])
        {
            int start = i;
            int current = i;
            int length = 0;
            do
            {
                length++;
                current = p[current];
                seen[current] = true;
            } while (current != start);

            cycle_lengths.push_back(length);
        }
    }

    // determine the lcm of the cycle_lengths
    long long res = 1;
    vector<int> exp(2e5 + 5);
    for (long long length : cycle_lengths)
    {
        vector<pair<int, int>> pf = prime_factorize(length);
        for (auto pe : pf)
        {
            exp[pe.first] = max(exp[pe.first], pe.second);
        }
    }

    for (int i = 2; i < 2e5 + 5; i++)
    {
        if (exp[i] != 0)
        {
            res = (res * modpow(i, exp[i], MOD)) % MOD;
        }
    }

    cout << res << endl;
}