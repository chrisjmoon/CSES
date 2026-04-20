#include <bits/stdc++.h>
using namespace std;

long long MOD = 1e9 + 7;

vector<long long> ft(1e6 + 5);
vector<long long> fti(1e6 + 5);

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

long long factorial(long long a)
{
    if (a == 1)
    {
        return 1;
    }

    return a * factorial(a - 1) % MOD;
}

long long factorial_inverse(long long a)
{
    if (a == 1)
    {
        return 1;
    }
    return modpow(a, MOD - 2) * factorial_inverse(a - 1) % MOD;
}

int main()
{
    int n;
    cin >> n;

    int MAX = 1e6 + 5;
    ft[0] = 1;
    fti[0] = 1;
    for (int i = 1; i < MAX; i++)
    {
        ft[i] = (i * ft[i - 1]) % MOD;
        fti[i] = (modpow(i, MOD - 2) * fti[i - 1]) % MOD;
    }

    for (int i = 0; i < n; i++)
    {
        int a, b;
        cin >> a >> b;

        long long res = ft[a];
        res = (res * fti[b]) % MOD;
        res = (res * fti[a - b]) % MOD;

        cout << res << endl;
    }
}