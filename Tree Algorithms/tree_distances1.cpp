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
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);

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

    // first pass - longest downward distance
    // second pass - pass to children the longest distance to a node outside the subtree

    vector<pair<int, int>> downward_distance(n);
    vector<int> maximal_distance(n, 0);
    auto dfs1 = [&](auto &&self, int parent, int current) -> int
    {
        int longest{};
        int second_longest{};
        for (auto neighbor : edges[current])
        {
            if (neighbor == parent)
            {
                continue;
            }

            int distance = self(self, current, neighbor) + 1;
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

        maximal_distance[current] = longest;
        downward_distance[current] = {longest, second_longest};

        return longest;
    };

    auto dfs2 = [&](auto &&self, int parent, int current, int max_outside) -> void
    {
        int longest_downward{downward_distance[current].first};
        maximal_distance[current] = max(maximal_distance[current], max_outside);

        for (auto neighbor : edges[current])
        {
            if (neighbor == parent)
            {
                continue;
            }

            int child_max_outside{longest_downward};
            if (longest_downward == downward_distance[neighbor].first + 1)
            {
                child_max_outside = downward_distance[current].second;
            }

            child_max_outside = max(child_max_outside, max_outside) + 1;

            self(self, current, neighbor, child_max_outside);
        }
    };

    dfs1(dfs1, -1, 0);
    dfs2(dfs2, -1, 0, 0);

    for (auto v : maximal_distance)
    {
        cout << v << " ";
    }
    cout << endl;
}
