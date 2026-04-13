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

vector<int> f;
void build(vector<int> &a)
{
    // f[i] is from i - lsb[i] + 1 -> i
    int n = a.size();

    f.resize(n + 1);

    // build prefix
    vector<int> p;
    p.push_back(0);
    int c = 0;
    for (int i = 0; i < n; i++)
    {
        c += a[i];
        p.push_back(c);
    }

    int l;
    c = 0;
    for (int i = 1; i <= n; i++)
    {
        l = i & (~i + 1);
        // f[i] is the sum from i - l -> i - 1;
        f[i] = p[i] - p[i - l];
    }
}

void update(int i, int v)
{
    i += 1;
    int l = i & (~i + 1);
    l /= 2;
    while (l)
    {
        f[i + l] += v;
        l /= 2;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long p;
    cin >> n >> p;

    vector<int> a(n, 1);
    build(a);

    vector<int> res;
    long k = 0;
    int l, r, m;
    // 0 1, 2, 3, 4, 5
    // 0, 1, 1, 2, 4, 5
    for (int i = 0; i < n; i++)
    {
        // find kth number through fenwick tree
        l = 0;
        r = n - i - 1;

        while (l < r)
        {
            m = (l + r) / 2;
            // calculate val at index m
            m += 1;
            int c = 0;
            for (int j = 0; j < m; j << 1)
            {
                if (m & j)
                {
                    c += f[j];
                }
            }
            m -= 1;

            if (c >= k)
            {
                r = m;
            }
            else
            {
                l = m + 1;
            }
        }
        res.push_back((l + r) / 2);

        k = (k + p - 1) % (n - i - 1);
    }

    for (auto v : res)
    {
        cout << v << " ";
    }
    cout << endl;
}
