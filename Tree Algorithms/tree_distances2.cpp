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

vector<vector<int>> edges;
vector<int> subtree_size;
vector<long> res;

// want to feed back up the sum of the distances of its children
// and the subtree size
// {distance sum, child subtree size}
pair<long, int> dfs1(int parent, int current)
{
    int current_subtree_size{1};
    long current_distance_sum{};
    for (auto neighbor : edges[current])
    {
        if (neighbor == parent)
        {
            continue;
        }

        auto [child_distance_sum, child_subtree_size] = dfs1(current, neighbor);
        current_subtree_size += child_subtree_size;
        current_distance_sum += child_distance_sum + child_subtree_size;
    }

    subtree_size[current] = current_subtree_size;
    return {current_distance_sum, current_subtree_size};
}

void dfs2(int parent, int current, long parent_total_sum)
{
    // adjust parent_total_sum
    // increase it by (N - S) where S is the size of the subtree rooted at current
    // decrease it by S
    res[current] = parent_total_sum + (edges.size() - 2 * subtree_size[current]);
    for (auto neighbor : edges[current])
    {
        if (neighbor == parent)
        {
            continue;
        }

        dfs2(current, neighbor, res[current]);
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    edges.resize(n);
    subtree_size.resize(n);
    res.resize(n);
    for (int i = 0; i < n - 1; i++)
    {
        int x, y;
        cin >> x >> y;
        x--;
        y--;

        edges[x].push_back(y);
        edges[y].push_back(x);
    }

    auto [root_distance_sum, tree_size] = dfs1(-1, 0);
    res[0] = root_distance_sum;

    for (int child : edges[0])
    {
        dfs2(0, child, root_distance_sum);
    }

    for (auto v : res)
    {
        cout << v << " ";
    }
    cout << endl;
}
