#include <bits/stdc++.h>
using namespace std;

long long MOD = 998244353;

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
            res = res * a % MOD;
            b -= 1;
        }

        a = a * a % MOD;
        b >>= 1;
    }

    return res;
}

long long choose(long long a, long long b, vector<long long> &f, vector<long long> &fi)
{
    long long res = 1;
    res = res * f[a] % MOD;
    res = res * fi[b] % MOD;
    res = res * fi[a - b] % MOD;

    return res;
}

int main()
{
    long long a, b, c;
    cin >> a >> b >> c;

    long long M = (a + b + c) + 5;
    // compute mod factorials and inverses
    vector<long long> f(M + 1), fi(M + 1);
    f[0] = 1;
    fi[0] = 1;
    for (long long i = 1; i <= M; i++)
    {
        f[i] = i * f[i - 1] % MOD;
    }

    fi[M] = modpow(f[M], MOD - 2);
    for (long long i = M - 1; i > 0; i--)
    {
        fi[i] = (i + 1) * fi[i + 1] % MOD;
    }

    long long res = 0;
    for (long long i = 0; i <= min(min(a, c), b + 1); i++)
    {
        long long temp = (i % 2) ? -1 : 1;
        temp = temp * choose(b + 1, i, f, fi) % MOD;
        temp = temp * choose(b + a - i, b, f, fi) % MOD;
        temp = temp * choose(b + c - i, b, f, fi) % MOD;

        res = (res + temp + MOD) % MOD;
    }

    cout << res << endl;
}