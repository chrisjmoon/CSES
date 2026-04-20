#include <bits/stdc++.h>
using namespace std;

long long MOD = 1e9 + 7;

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

int main()
{
    string s;
    cin >> s;

    long long n = s.size();

    // compute factorial
    // compute factorial inverse
    vector<long long> f(n + 1);
    vector<long long> fi(n + 1);
    f[0] = 1;
    fi[0] = 1;
    for (int i = 1; i <= n; i++)
    {
        f[i] = (i * f[i - 1]) % MOD;
    }
    fi[n] = modpow(f[n], MOD - 2);
    for (int i = n - 1; i >= 1; i--)
    {
        fi[i] = ((i + 1) * fi[i + 1]) % MOD;
    }

    vector<int> cnt(26);
    for (int i = 0; i < n; i++)
    {
        cnt[s[i] - 'a']++;
    }
    long long denom = 1;
    for (int i = 0; i < 26; i++)
    {
        denom = (denom * fi[cnt[i]]) % MOD;
    }

    cout << (f[n] * denom) % MOD << endl;
}