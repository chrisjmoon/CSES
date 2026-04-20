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

int main()
{
    int n;
    cin >> n;
    vector<int> x(n);
    long long res = 0;
    vector<long long> freq(1e6 + 5);
    for (int i = 0; i < n; i++)
    {
        cin >> x[i];

        // PIE
        vector<pair<int, int>> pf = prime_factorize(x[i]);
        int k = pf.size();
        res += i;
        for (int mask = 1; mask < (1 << k); mask++)
        {
            int bits = 0;
            long long div = 1;
            for (int i = 0; i < k; i++)
            {
                if (mask & (1 << i))
                {
                    bits++;
                    div *= pf[i].first;
                }
            }
            freq[div] += 1;

            if (bits % 2 == 0)
            {
                res += (freq[div] - 1);
            }
            else
            {
                res -= (freq[div] - 1);
            }
        }
    }

    cout << res << endl;
}