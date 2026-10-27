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

void dfs(vector<vector<int>> &edges, vector<vector<int>> &binary_lift, vector<int> &depth,
         int current, int parent)
{
    for (int neighbor : edges[current])
    {
        if (neighbor == parent)
        {
            continue;
        }

        binary_lift[neighbor][0] = current;
        depth[neighbor] = depth[current] + 1;
        dfs(edges, binary_lift, depth, neighbor, current);
    }
}

int calculate_lca(vector<vector<int>> &binary_lift, vector<int> &depth, int x, int y)
{
    if (depth[x] > depth[y])
    {
        swap(x, y);
    }

    // raise y until it has the same depth as x
    int gap = depth[y] - depth[x];
    const int K = binary_lift[0].size() - 1;
    for (int shift = 0; shift <= K; shift++)
    {
        if ((1 << shift) & gap)
        {
            y = binary_lift[y][shift];
        }
    }

    if (x == y)
    {
        return x;
    }

    // jump large to small
    for (int shift = K; shift >= 0; shift--)
    {
        if (binary_lift[x][shift] != binary_lift[y][shift])
        {
            x = binary_lift[x][shift];
            y = binary_lift[y][shift];
        }
    }

    return binary_lift[x][0];
}

void propagate_update(vector<int> &res, vector<int> &update, vector<vector<int>> &edges,
                      int current, int parent)
{
    for (int neighbor : edges[current])
    {
        if (neighbor == parent)
        {
            continue;
        }

        propagate_update(res, update, edges, neighbor, current);
        res[current] += res[neighbor];
    }

    res[current] += update[current];
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

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

    static const int K = ceil(log2(n));
    vector<vector<int>> binary_lift(n, vector<int>(K + 1, -1));
    vector<int> depth(n);
    depth[0] = 0;

    dfs(edges, binary_lift, depth, 0, -1);

    // fill out binary lift table
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

    vector<int> update(n, 0);
    while (q--)
    {
        int x, y;
        cin >> x >> y;
        x--;
        y--;

        int lca = calculate_lca(binary_lift, depth, x, y);
        update[x]++;
        update[y]++;
        update[lca]--;
        if (binary_lift[lca][0] != -1)
        {
            update[binary_lift[lca][0]]--;
        }
    }

    vector<int> res(n, 0);
    propagate_update(res, update, edges, 0, -1);

    for (int i = 0; i < n; i++)
    {
        cout << res[i] << " ";
    }
    cout << endl;
}
