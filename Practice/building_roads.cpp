#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define vi vector<int>
#define vii vector<pair<int, int>>
#define pii pair<int, int>
#define rep(i, a, b) for (int i = a; i < b; ++i)
#define all(v) v.begin(), v.end()
#define pb push_back
#define endl "\n"

const long long MOD = 998244353;

struct mint
{
    long long value;

    mint(long long value_ = 0)
    {
        value = value_ % MOD;
        if (value < 0)
        {
            value += MOD;
        }
    }

    mint &operator+=(const mint &other)
    {
        value = (value + other.value) % MOD;
        return *this;
    }

    mint &operator-=(const mint &other)
    {
        value = (value - other.value) % MOD;
        if (value < 0)
        {
            value += MOD;
        }
        return *this;
    }

    mint &operator*=(const mint &other)
    {
        value = (value * other.value) % MOD;
        return *this;
    }

    static mint modpow(mint base, long long exp)
    {
        mint res = 1;
        if (exp == 0)
        {
            return res;
        }

        while (exp > 0)
        {
            if (exp & 1)
            {
                res *= base;
                exp -= 1;
            }

            base *= base;
            exp >>= 1;
        }

        return res;
    }

    static mint inverse(mint a)
    {
        return modpow(a, MOD - 2);
    }

    mint &operator/=(const mint &other)
    {
        value = value * inverse(other).value % MOD;
        return *this;
    }

    friend mint operator+(mint a, mint const &b)
    {
        return a += b;
    }

    friend mint operator-(mint a, mint const &b)
    {
        return a -= b;
    }

    friend mint operator*(mint a, mint const &b)
    {
        return a *= b;
    }

    friend mint operator/(mint a, mint const &b)
    {
        return a /= b;
    }
};

// Utility functions
ll gcd(ll a, ll b)
{
    return b == 0 ? a : gcd(b, a % b);
}
ll lcm(ll a, ll b)
{
    return (a / gcd(a, b)) * b;
}

// print vector
template <typename T> void print_vector(const std::vector<T> &vec)
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

int digits(ll x)
{
    return to_string(x).size();
}

vector<int> id;
vector<int> cs;

int find_id(int x)
{
    if (x == id[x])
    {
        return x;
    }

    id[x] = find_id(id[x]); // flattening the representation
    return id[x];
}

bool join(int x, int y)
{
    int idx{find_id(x)}, idy{find_id(y)};

    if (idx == idy)
    {
        return false;
    }

    if (cs[idx] > cs[idy])
    {
        swap(idx, idy);
        swap(x, y);
    }

    id[idy] = idx;

    int ts = cs[idx] + cs[idy];
    cs[idx] = ts;
    cs[idy] = ts;

    return true;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    int m;

    cin >> n >> m;
    id.resize(n);
    cs.resize(n, 1);

    iota(id.begin(), id.end(), 0);

    int cc{n};

    for (int i = 0; i < m; i++)
    {
        int x, y;
        cin >> x >> y;
        x--;
        y--;

        cc -= join(x, y);
    }

    if (cc == 1)
    {
        cout << 0 << endl;
        return 0;
    }

    // representatives of the connected components
    set<int> srp;
    vector<int> rp;
    for (int i = 0; i < n; i++)
    {
        if (!srp.contains(find_id(i)))
        {
            rp.push_back(find_id(i));
        }
        srp.insert(find_id(i));
    }

    cout << cc - 1 << endl;
    for (int i = 1; i < rp.size(); i++)
    {
        cout << rp[i - 1] + 1 << " " << rp[i] + 1 << endl;
    }
}
