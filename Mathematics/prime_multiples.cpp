#include <bits/stdc++.h>
using namespace std;

using ll = unsigned long long;

int main()
{
    ll n;
    int k;
    cin >> n >> k;

    vector<ll> p(k);
    for (int i = 0; i < k; i++)
    {
        cin >> p[i];
    }

    // PIE
    ll res = 0;
    for (int mask = 1; mask < (1 << k); mask++)
    {
        ll div = 1;
        int primes = 0;
        bool ok = true;
        for (int i = 0; i < k; i++)
        {
            if (mask & (1 << i))
            {
                primes++;
                if (div > n / p[i]) // avoid overflow
                {
                    ok = false;
                    break;
                }
                div *= p[i];
            }
        }

        if (!ok)
        {
            continue;
        }

        ll cur = n / div;
        if (primes % 2 == 0)
        {
            cur *= -1;
        }

        res += cur;
    }

    cout << res << endl;
}