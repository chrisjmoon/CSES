#include <bits/stdc++.h>

using namespace std;
#define ll unsigned long long

int main()
{
    ll n;
    cin >> n;

    ll res = (ll)popcount(n);
    while (n)
    {
        ll x = countr_zero(n);
        ll pc = popcount(n);

        // (n choose 1) * 1 + (n choose 2) * 2 + ...
        // sum_{i = 1}^n (n choose i) * i
        // n2^(n - 1)

        ll a = x == 0 ? 0 : (1ULL << (x - 1)) * x;
        ll b = (pc - 1) * (1ULL << x);

        res += a + b;

        n &= n - 1;
    }

    cout << res << endl;
}