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

vector<int> fenwick;

// update position x with value v
void update(int x, int v)
{
    x += 1; // we increment because our FT is 1-indexed
    int N = fenwick.size();
    while (x < N)
    {
        fenwick[x] += v;
        x += x & -x;
    }
}

int sum(int x)
{
    x += 1;
    int res{};
    while (x > 0)
    {
        res += fenwick[x];
        x -= x & -x;
    }

    return res;
}

int find_kth(int k)
{
    int N = fenwick.size() - 1;
    int step = std::bit_floor((unsigned int)N);

    int pos{};
    while (step)
    {
        int next = pos + step;
        if (next <= N && fenwick[next] < k)
        {
            k -= fenwick[next];
            pos = next;
        }

        step >>= 1;
    }

    return pos + 1;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    int m;

    cin >> n >> m;

    // 1. we coordinate compress the tickets
    // 2. build the fenwick tree
    // 3. for each customer with preference c, determine the largest ticket price p such that
    //   p <= c; call it P
    // 4. let k = idx(P), as in the compressed coordinate; if fenwick_sum(k) == 0 -> -1
    //   otherwise, determine the ith element in our BIT

    vector<int> p(n);
    vector<int> cc; // coordinate compression
    for (int i = 0; i < n; i++)
    {
        cin >> p[i];
        cc.push_back(p[i]);
    }

    sort(cc.begin(), cc.end());
    cc.erase(unique(cc.begin(), cc.end()), cc.end());

    int N = cc.size(); // size of our coordinate compression
    fenwick.resize(N + 1);

    for (int i = 0; i < n; i++)
    {
        int j = lower_bound(cc.begin(), cc.end(), p[i]) - cc.begin();
        update(j, 1);
    }

    for (int i = 0; i < m; i++)
    {
        int customer_price;
        cin >> customer_price;

        // determine the largest ticket price p <= customer_price
        int j = upper_bound(cc.begin(), cc.end(), customer_price) - cc.begin();

        if (j == 0)
        {
            cout << -1 << endl;
            continue;
        }

        j--;
        // determine the number of tickets that are <= j
        int num_tickets{sum(j)};

        if (num_tickets == 0)
        {
            cout << -1 << endl;
            continue;
        }
        // find the ticket that is the num_tickets-th in the fenwick tree

        int ticket_index = find_kth(num_tickets) - 1;
        cout << cc[ticket_index] << endl;

        update(ticket_index, -1);
    }
}
