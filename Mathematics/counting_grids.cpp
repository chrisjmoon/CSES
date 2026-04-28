#include <bits/stdc++.h>
using namespace std;

long long MOD = 1e9 + 7;
long long PHI = MOD - 1;

long long modpow(long long a, long long b, long long MOD)
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
            res = res * a % MOD;
            b -= 1;
        }

        a = a * a % MOD;
        b >>= 1;
    }

    return res;
}

int main()
{
    long long n;
    cin >> n;

    // identity fixed set size is 2^(n^2)
    // rotation by 1, 3
    //   if n is even: (n/2)(n/2 + 1) - n/2
    //   if n is odd: 1 + ((n - 1)/2)((n - 1)/2 + 1)
    // rotation by 2
    //   if n is even: n*n/2
    //   if n is odd: n(floor(n/2)) + ceil(n/2)

    long long exp = n * n % PHI;
    long long fixed = modpow(2, exp, MOD);
    if (n % 2)
    {
        long long c = ((n - 1) / 2) * ((n + 1) / 2) % PHI;
        c = (c + 1) % PHI;
        c = modpow(2, c, MOD);
        c = c * 2 % MOD;

        long long d = n / 2;
        d = d * n % PHI;
        d = (d + (n + 1) / 2) % PHI;
        d = modpow(2, d, MOD);

        fixed = (fixed + c + d) % MOD;
    }
    else
    {
        long long c = n / 2;
        c = c * (c + 1) % PHI;
        c = (c - n / 2 + PHI) % PHI;
        c = modpow(2, c, MOD);
        c = c * 2 % MOD;

        long long d = n / 2;
        d = d * n % PHI;
        d = modpow(2, d, MOD);

        fixed = (fixed + c + d) % MOD;
    }

    fixed = fixed * modpow(4, MOD - 2, MOD) % MOD;
    cout << fixed << endl;
}