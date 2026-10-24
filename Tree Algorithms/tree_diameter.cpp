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

int res{};

int dfs(vector<vector<int>> &edges, int parent, int current)
{
    int m1{}, m2{};
    for (auto neighbor : edges[current])
    {
        if (neighbor == parent)
        {
            continue;
        }

        int distance = dfs(edges, current, neighbor) + 1;
        if (distance >= m1)
        {
            m2 = m1;
            m1 = distance;
        }
        else if (distance >= m2)
        {
            m2 = distance;
        }
    }

    res = max(res, m1 + m2);

    return m1;
}

int tree_diameter(const std::vector<std::vector<int>> &graph)
{
    if (graph.empty())
    {
        return 0;
    }

    std::vector<int> parent(graph.size(), -1);
    std::vector<int> order;
    order.reserve(graph.size());
    order.push_back(0);

    for (std::size_t i = 0; i < order.size(); ++i)
    {
        int current = order[i];

        for (int neighbor : graph[current])
        {
            if (neighbor == parent[current])
            {
                continue;
            }

            parent[neighbor] = current;
            order.push_back(neighbor);
        }
    }

    std::vector<int> height(graph.size());
    int diameter{};

    for (auto it = order.rbegin(); it != order.rend(); ++it)
    {
        int current = *it;
        int longest{};
        int second_longest{};

        for (int neighbor : graph[current])
        {
            if (neighbor == parent[current])
            {
                continue;
            }

            int distance = height[neighbor] + 1;
            if (distance > longest)
            {
                second_longest = longest;
                longest = distance;
            }
            else if (distance > second_longest)
            {
                second_longest = distance;
            }
        }

        height[current] = longest;
        diameter = std::max(diameter, longest + second_longest);
    }

    return diameter;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

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

    cout << tree_diameter(edges) << endl;
}
