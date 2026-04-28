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
    string s;
    cin >> n;
    cin >> s;

    if (n % 2)
    {
        cout << 0 << endl;
        return 0;
    }

    if (s.size() == n)
    {
        cout << 1 << endl;
        return 0;
    }

    int k = 0;
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == '(')
        {
            k++;
        }
        else
        {
            k--;
            if (k < 0)
            {
                cout << 0 << endl;
                return 0;
            }
        }
    }

    // calculate (2m + k choose m) - (2m + k choose m - 1)
    int m = (n - s.size() - k) / 2;
    vector<long long> f(2 * m + k + 1);
    vector<long long> fi(2 * m + k + 1);
    f[0] = 1;
    for (int i = 1; i <= 2 * m + k; i++)
    {
        f[i] = (i * f[i - 1]) % MOD;
    }

    fi[2 * m + k] = modpow(f[2 * m + k], MOD - 2, MOD);
    for (int i = 2 * m + k - 1; i >= 0; i--)
    {
        fi[i] = (i + 1) * fi[i + 1] % MOD;
    }

    long long res = f[2 * m + k] * fi[m] % MOD;
    res = res * fi[m + k] % MOD;

    long long diff = f[2 * m + k] * fi[m - 1] % MOD;
    diff = diff * fi[m + k + 1] % MOD;

    cout << (res - diff + MOD) % MOD << endl;
}