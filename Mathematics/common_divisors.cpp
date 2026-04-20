#include <bits/stdc++.h>
using namespace std;

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
        for (int i = 1; i <= exp; i++)
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
    int n;
    cin >> n;
    vector<int> x(n);
    vector<int> cnt(1e6 + 5);
    int MAX = 0;
    for (int i = 0; i < n; i++)
    {
        cin >> x[i];
        cnt[x[i]]++;
        MAX = max(MAX, x[i]);
    }

    // prime factorize each number
    // collect all divisors
    vector<bool> sieve(MAX + 1);
    for (int i = 0; i < n; i++)
    {
        for (auto div : divisors(x[i]))
        {
            sieve[div] = true;
        }
    }

    vector<int> sieved_divisors;
    for (int i = 1; i <= MAX; i++)
    {
        if (sieve[i])
        {
            sieved_divisors.push_back(i);
        }
    }

    reverse(sieved_divisors.begin(), sieved_divisors.end());
    for (auto v : sieved_divisors)
    {
        int div_count = 0;
        for (int i = v; i <= MAX; i += v)
        {
            div_count += cnt[i];
            if (div_count >= 2)
            {
                break;
            }
        }

        if (div_count >= 2)
        {
            cout << v << endl;
            return 0;
        }
    }
}