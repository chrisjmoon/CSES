#include <bits/stdc++.h>
using namespace std;

long long MOD = 1e9 + 7;

int main()
{
    long long n;
    cin >> n;

    // matrix
    // a b
    // c d
    // squaring the matrix yields:
    // a * a + b * c || a * b + b * d
    // c * a + d * c || c * b + d * d
    // when b is odd
    // 1 1

    if (n == 0)
    {
        cout << 0 << endl;
        return 0;
    }

    long long a = 1, b = 0, c = 0, d = 1;     // result
    long long ba = 1, bb = 1, bc = 1, bd = 0; // base
    n -= 1;
    while (n > 0)
    {
        if (n & 1)
        {
            long long e, f, g, h;
            e = (ba * a + bb * c) % MOD;
            f = (ba * b + bb * d) % MOD;
            g = (bc * a + bd * c) % MOD;
            h = (bc * b + bd * d) % MOD;
            a = e;
            b = f;
            c = g;
            d = h;
            n -= 1;
        }

        long long e, f, g, h;
        // square the base
        e = ba * ba % MOD;
        e = (e + bb * bc) % MOD;
        f = ba * bb % MOD;
        f = (f + bb * bd) % MOD;
        g = bc * ba % MOD;
        g = (g + bd * bc) % MOD;
        h = bc * bb % MOD;
        h = (h + bd * bd) % MOD;
        ba = e;
        bb = f;
        bc = g;
        bd = h;

        n >>= 1;
    }

    cout << a << endl;
}