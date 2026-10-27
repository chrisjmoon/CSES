#include <bits/stdc++.h>
using namespace std;

#define FAST_IO                                                                                    \
    ios_base::sync_with_stdio(false);                                                              \
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

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    int q;
    cin >> q;

    static const int K = ceil(log2(n));

    vector<vector<int>> pk(n, vector<int>(K + 1, -1));
    vector<vector<int>> children(n);

    for (int i = 0; i < n - 1; i++)
    {
        int p;
        cin >> p;
        p--;

        pk[i + 1][0] = p;
        children[p].push_back(i + 1);
    }

    for (int jump = 1; jump <= K; jump++)
    {
        for (int i = 0; i < n; i++)
        {
            int intermediate_boss{pk[i][jump - 1]};
            if (intermediate_boss != -1)
            {
                pk[i][jump] = pk[intermediate_boss][jump - 1];
            }
        }
    }

    vector<int> depth(n);
    depth[0] = 0;

    auto dfs = [&](auto &&self, int parent, int current) -> void
    {
        depth[current] = depth[parent] + 1;
        for (int child : children[current])
        {
            self(self, current, child);
        }
    };

    for (int child : children[0])
    {
        dfs(dfs, 0, child);
    }

    while (q--)
    {
        int x, y;
        cin >> x >> y;
        x--;
        y--;

        if (depth[x] > depth[y])
        {
            swap(x, y);
        }

        // x is more shallow in the tree
        // bring y up to x

        int gap{depth[y] - depth[x]};
        for (int shift = 0; shift <= K && (1 << shift) <= gap; shift++)
        {
            if ((1 << shift) & gap)
            {
                y = pk[y][shift];
            }
        }

        if (x == y)
        {
            cout << x + 1 << endl;
            continue;
        }

        for (int shift = K; shift >= 0; shift--)
        {
            if (pk[x][shift] != pk[y][shift])
            {
                x = pk[x][shift];
                y = pk[y][shift];
            }
        }

        cout << pk[x][0] + 1 << endl;
    }
}
