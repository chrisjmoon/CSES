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

int main()
{

    int n, m;
    cin >> n >> m;

    // want to determine if there is a connection
    // from node 1 to node n
    // if such a connection exists, we want to determine
    // the shortest route

    vector<vector<int>> edges(n);
    for (int i = 0; i < m; i++)
    {
        int x, y;
        cin >> x >> y;
        x--;
        y--;

        edges[x].push_back(y);
        edges[y].push_back(x);
    }

    vector<int> history(n, -1);
    queue<int> q;
    history[0] = 0;
    q.push(0);

    while (q.size())
    {
        int v = q.front();
        q.pop();

        for (auto neighbor : edges[v])
        {
            if (history[neighbor] != -1)
            {
                continue;
            }

            history[neighbor] = v;
            if (neighbor == n - 1)
            {
                break;
            }
            q.push(neighbor);
        }
    }

    if (history[n - 1] == -1)
    {
        cout << "IMPOSSIBLE" << endl;
        return 0;
    }

    vector<int> route_history{n - 1};
    while (route_history.back() != 0)
    {
        route_history.push_back(history[route_history.back()]);
    }

    cout << route_history.size() << endl;
    for (int i = route_history.size() - 1; i >= 0; i--)
    {
        cout << route_history[i] + 1 << " ";
    }
    cout << endl;
}
