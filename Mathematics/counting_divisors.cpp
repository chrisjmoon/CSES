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
    int q;
    cin >> q;

    for (int i = 0; i < q; i++)
    {
        int x;
        cin >> x;

        vector<pair<int, int>> pf = prime_factorize(x);
        int res = 1;
        for (auto pe : pf)
        {
            res *= (pe.second + 1);
        }

        cout << res << endl;
    }
}