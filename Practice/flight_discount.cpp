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

using connection = pair<ll, int>;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<connection>> edges(n);
    for (int i = 0; i < m; i++)
    {
        int x, y;
        ll distance;

        cin >> x >> y >> distance;
        x--;
        y--;

        edges[x].emplace_back(distance, y);
    }

    // distance, city, discount used
    using flight_state = tuple<ll, int, bool>;
    priority_queue<flight_state, vector<flight_state>, greater<flight_state>> pq;

    // first dim is city, second dim is whether we used the discount
    vector<vector<ll>> shortest_distance(n, vector<ll>(2, numeric_limits<ll>::max()));
    shortest_distance[0][0] = 0;

    pq.emplace(0, 0, false);
    while (!pq.empty())
    {
        auto [distance, city, discount_used] = pq.top();
        pq.pop();

        if (distance > shortest_distance[city][discount_used])
        {
            continue;
        }

        for (auto [weight, next_city] : edges[city])
        {
            auto next_distance = distance + weight;

            if (next_distance < shortest_distance[next_city][discount_used])
            {
                shortest_distance[next_city][discount_used] = next_distance;
                pq.emplace(next_distance, next_city, discount_used);
            }

            if (!discount_used)
            {
                ll discount_weight = weight / 2;
                auto discount_distance = distance + discount_weight;
                if (discount_distance < shortest_distance[next_city][true])
                {
                    shortest_distance[next_city][true] = discount_distance;
                    pq.emplace(discount_distance, next_city, true);
                }
            }
        }
    }

    cout << shortest_distance[n - 1][true] << endl;
}
