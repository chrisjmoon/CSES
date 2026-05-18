#include <bits/stdc++.h>
using namespace std;

vector<long long> ltree, rtree, p;
int base = 1;
long long INF = 1e16;

void build()
{
    int n = p.size();
    while (base < n)
    {
        base *= 2;
    }

    ltree.resize(2 * base, INF);
    rtree.resize(2 * base, INF);

    // left: p_j + i - j = (p_j - j) + i
    // right: p_j + j - i = (p_j + j) - i
    for (int i = 0; i < n; i++)
    {
        ltree[base + i] = p[i] - i;
        rtree[base + i] = p[i] + i;
    }
    for (int i = base - 1; i > 0; i--)
    {
        ltree[i] = min(ltree[2 * i], ltree[2 * i + 1]);
        rtree[i] = min(rtree[2 * i], rtree[2 * i + 1]);
    }
}

long long query(int node, int i, int j, int e, int f, bool left)
{
    // If the query range is completely outside the current segment
    if (e > j || f < i)
    {
        return 1e18; // Return infinity
    }
    // If the current segment is completely inside the query range
    if (e <= i && j <= f)
    {
        return left ? ltree[node] : rtree[node];
    }

    int k = (i + j) / 2;
    return min(query(2 * node, i, k, e, f, left), query(2 * node + 1, k + 1, j, e, f, left));
}

void update(int i, int new_price, bool left)
{
    vector<long long> &tree = left ? ltree : rtree;
    tree[base + i] = left ? new_price - i : new_price + i;
    int j = (base + i) / 2;
    while (j > 0)
    {
        tree[j] = min(tree[2 * j], tree[2 * j + 1]);
        j /= 2;
    }
}

int main()
{
    int n, q;
    cin >> n >> q;

    p.resize(n);
    for (int i = 0; i < n; i++)
    {
        cin >> p[i];
    }

    build();
    vector<long long> res;
    while (q--)
    {
        int query_type;
        cin >> query_type;

        if (query_type == 1)
        {
            int k, new_price;
            cin >> k >> new_price;
            k--;
            update(k, new_price, true);
            update(k, new_price, false);
        }
        else
        {
            int k;
            cin >> k;
            k--;

            long long left_min = query(1, 0, base - 1, 0, k, true) + k;
            long long right_min = query(1, 0, base - 1, k, n - 1, false) - k;
            res.push_back(min(left_min, right_min));
        }
    }

    for (auto v : res)
    {
        cout << v << endl;
    }
}