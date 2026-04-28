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
    int n, m;
    cin >> n >> m;

    // use Burnside's lemma to determine the number of orbits
    // orbits collapse necklaces equal up to rotation
    // size of |X/G| = \sum_{g \in G} |X^g|
    // need to determine x such that rotation by i is still x
    // |G| = n
    long long res = 0;
    for (int i = 1; i <= n; i++)
    {
        int j = gcd(i, n);
        res = (res + modpow(m, j, MOD)) % MOD;
    }

    res = res * modpow(n, MOD - 2, MOD) % MOD;

    cout << res << endl;
}