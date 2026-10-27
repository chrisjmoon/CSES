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

void dfs(vector<vector<int>> &edges, vector<int> &depth, vector<vector<int>> &binary_lift,
         int current, int parent)
{
    if (current != 0)
    {
        depth[current] = depth[parent] + 1;
        binary_lift[current][0] = parent;
    }

    for (int neighbor : edges[current])
    {
        if (neighbor == parent)
        {
            continue;
        }

        dfs(edges, depth, binary_lift, neighbor, current);
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    int q;
    cin >> q;

    vector<vector<int>> edges(n);
    for (int i = 0; i < n - 1; i++)
    {
        int x, y;
        cin >> x >> y;
        x--;
        y--;

        edges[x].push_back(y);
        edges[y].push_back(x);
    }

    // root at 0
    vector<int> depth(n);
    depth[0] = 0;

    static const int K = ceil(log2(n));
    vector<vector<int>> binary_lift(n, vector<int>(K + 1, -1));

    dfs(edges, depth, binary_lift, 0, -1);

    // fill out binary lift
    for (int shift = 1; shift <= K; shift++)
    {
        for (int i = 0; i < n; i++)
        {
            int intermediate_jump = binary_lift[i][shift - 1];
            if (intermediate_jump != -1)
            {
                binary_lift[i][shift] = binary_lift[intermediate_jump][shift - 1];
            }
        }
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

        int dx = depth[x];
        int dy = depth[y];

        // determine the LCA of x and y
        int gap = dy - dx;
        for (int shift = 0; shift <= K; shift++)
        {
            if ((1 << shift) & gap)
            {
                y = binary_lift[y][shift];
            }
        }

        // x and y are at the same depth now

        int lca;
        if (x != y)
        {
            for (int shift = K; shift >= 0; shift--)
            {
                if (binary_lift[x][shift] != binary_lift[y][shift])
                {
                    x = binary_lift[x][shift];
                    y = binary_lift[y][shift];
                }
            }

            lca = binary_lift[x][0];
        }
        else
        {
            lca = x;
        }

        int dlca = depth[lca];

        cout << (dx - dlca) + (dy - dlca) << endl;
    }
}
