#include <bits/stdc++.h>
using namespace std;

long long MOD = 1e9 + 7;

long long exp(long long a, long long b)
{
    b %= (MOD - 1);
    if (b == 0)
    {
        return 1;
    }
    if (b == 1)
    {
        return a % MOD;
    }

    long long res = exp(a, b / 2);
    res = (res * res) % MOD;
    if (b % 2)
    {
        res = (res * a) % MOD;
    }

    return res;
}

int main()
{
    int q;
    cin >> q;

    for (int i = 0; i < q; i++)
    {
        long long a, b;
        cin >> a >> b;
        cout << exp(a, b) << endl;
    }
}