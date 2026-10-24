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
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // minimum price of route
    // how many minimum price routes are there
    // what is the min/max number of flights in a min price route

    int n, m;
    cin >> n >> m;

    vector<vector<pair<ll, int>>> edges(n);
    for (int i = 0; i < m; i++)
    {
        int x, y;
        ll price;

        cin >> x >> y >> price;
        x--;
        y--;

        edges[x].emplace_back(price, y);
    }

    // we want to record for each city the min price
    // the total number of routes
    // the max/min number of flights in a min price route

    pair<int, int> DEFAULT = {numeric_limits<int>::max(), 0};

    vector<ll> min_price(n, numeric_limits<ll>::max());
    vector<int> num_routes(n);
    vector<pair<int, int>> num_flights(n, DEFAULT);

    // price, flights, city
    using connection = tuple<ll, int, int>;
    priority_queue<connection, vector<connection>, greater<connection>> pq;
    pq.emplace(0, 0, 0);

    while (!pq.empty())
    {
        auto [price, flights, city] = pq.top();
        pq.pop();

        if (price > min_price[city])
        {
            continue;
        }

        for (auto [weight, next_city] : edges[city])
        {
            auto next_price = price + weight;

            if (next_price > min_price[next_city])
            {
                continue;
            }
            else if (next_price == min_price[next_city])
            {
                num_routes[next_city]++;
                auto &nf = num_flights[next_city];

                nf.first = min(nf.first, flights + 1);
                nf.second = max(nf.second, flights + 1);
            }
            else
            {
                min_price[next_city] = next_price;
                num_routes[next_city] = 1;
                num_flights[next_city] = {flights + 1, flights + 1};
            }

            pq.emplace(next_price, flights + 1, next_city);
        }
    }

    cout << min_price[n - 1] << " ";
    cout << num_routes[n - 1] << " ";
    cout << num_flights[n - 1].first << " ";
    cout << num_flights[n - 1].second << endl;
}
