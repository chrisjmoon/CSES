#include <bits/stdc++.h>
using namespace std;

long long MOD = 1e9 + 7;

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
            res = (res * a) % MOD;
            b -= 1;
        }

        a = (a * a) % MOD;
        b >>= 1;
    }

    return res;
}

int main()
{
    int n;
    cin >> n;

    if (n % 2)
    {
        cout << 0 << endl;
        return 0;
    }

    // let 2m = n
    // (n choose m) - (n choose m - 1)
    int m = n / 2;

    vector<long long> f(n + 1);
    vector<long long> fi(n + 1);
    f[0] = 1;
    for (int i = 1; i <= n; i++)
    {
        f[i] = (i * f[i - 1]) % MOD;
    }

    fi[n] = modpow(f[n], MOD - 2, MOD);
    for (int i = n - 1; i >= 0; i--)
    {
        fi[i] = (i + 1) * fi[i + 1] % MOD;
    }

    long long res = f[n];
    res = res * fi[m] % MOD;
    res = res * fi[m] % MOD;

    long long diff = f[n];
    diff = diff * fi[m - 1] % MOD;
    diff = diff * fi[m + 1] % MOD;

    cout << (res - diff + MOD) % MOD << endl;
}