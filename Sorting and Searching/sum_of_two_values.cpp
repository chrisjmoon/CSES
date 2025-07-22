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

    int n;
    long x;
    cin >> n >> x;
    vector<pair<long, long>> a;
    for (int i = 0; i < n; i++)
    {
        long w;
        cin >> w;
        a.emplace_back(w, i);
    }

    sort(a.begin(), a.end(), [](pair<long, long> x, pair<long, long> y)
         { return x.first < y.first; });
    int i, j;
    i = 0;
    j = n - 1;
    while (i < j)
    {
        // cout << a[i].first << " " << a[j].first << endl;
        if ((a[i].first + a[j].first) == x)
        {
            break;
        }
        if ((a[i].first + a[j].first) > x)
        {
            j--;
        }
        else
        {
            i++;
        }
    }

    if (i == j)
    {
        cout << "IMPOSSIBLE" << endl;
    }
    else
    {
        cout << a[i].second + 1 << " " << a[j].second + 1 << endl;
    }
}
