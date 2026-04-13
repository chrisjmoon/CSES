#include <bits/stdc++.h>
using namespace std;

#define FAST_IO                       \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);

// int: 32 bits -+ 2**9
// long: 32 or 64 bits depending on the platform
// long long: 64 bits -+ 9**18
#define ll long long
#define vi vector<int>
#define vii vector<pair<int, int>>
#define pii pair<int, int>
#define rep(i, a, b) for (int i = a; i < b; ++i)
#define all(v) v.begin(), v.end()
#define pb push_back
#define endl "\n"

// Constants
const int MOD = 1e9 + 7;
const int INF = 1e9;

// Utility functions
ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }
ll lcm(ll a, ll b) { return (a / gcd(a, b)) * b; }

// print vector
template <typename T>
void print_vector(const std::vector<T> &vec)
{
    for (const T &x : vec)
    {
        std::cout << x << " ";
    }
    std::cout << '\n';
}

// binary exponentiation
ll pow(ll x, ll y, ll MOD = 0)
{
    ll res = 1;
    while (y > 0)
    {
        if (y % 2)
        {
            res *= x;
            if (MOD != 0)
                res %= MOD;
            y -= 1;
        }
        else
        {
            x *= x;
            if (MOD != 0)
                x %= MOD;
            y /= 2;
        }
    }

    return res;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long x;
    int n;
    cin >> x >> n;

    long p;
    set<long> l = {0, x};
    multiset<long> s = {x};
    while (n--)
    {
        cin >> p;
        // determine what segment p is part of
        auto ub = l.upper_bound(p);
        auto lb = prev(ub);

        // cout << "lb, ub: " << *lb << " " << *ub << endl;
        // split the segment
        long e = p - *lb;
        long f = *ub - p;
        l.insert(p);

        s.erase(s.find(e + f));
        s.insert(e);
        s.insert(f);
        cout << *s.rbegin() << endl;
    }
}
