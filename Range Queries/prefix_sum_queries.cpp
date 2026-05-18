#include <bits/stdc++.h>
using namespace std;

vector<int> x;
vector<long long> tree;
vector<long long> lazy;
int base = 1;

void build()
{
    int n = x.size();
    while (base < n)
    {
        base *= 2;
    }

    tree.resize(2 * base);
    lazy.resize(2 * base);
    long long prefix_sum = 0;
    for (int i = 0; i < n; i++)
    {
        prefix_sum += x[i];
        tree[base + i] = prefix_sum;
    }

    for (int i = base - 1; i >= 0; i--)
    {
        tree[i] = max(tree[2 * i], tree[2 * i + 1]);
    }
}

// get maximum prefix sum in the range e, f
long long query(int node, int i, int j, int e, int f, long long lazy_prop)
{
    if (i == j)
    {
        return tree[node] + lazy_prop;
    }

    lazy_prop += lazy[node];
    int k = (i + j) / 2;
    if (f <= k)
    {
        return query(2 * node, i, k, e, f, lazy_prop);
    }
    else if (k < e)
    {
        return query(2 * node + 1, k + 1, j, e, f, lazy_prop);
    }
    else
    {
        return max(query(2 * node, i, k, e, min(k, f), lazy_prop),
                   query(2 * node + 1, k + 1, j, max(k + 1, e), f, lazy_prop));
    }
}

void update(int node, int i, int j, int e, int f, int delta)
{
    if (e > f)
    {
        return;
    }
    if (i == e && j == f)
    {
        lazy[node] += delta;
        tree[node] += delta;
        return;
    }

    int k = (i + j) / 2;
    update(2 * node, i, k, e, min(k, f), delta);
    update(2 * node + 1, k + 1, j, max(k + 1, e), f, delta);
    tree[node] = max(tree[2 * node], tree[2 * node + 1]) + lazy[node];
}

int main()
{
    int n, q;
    cin >> n >> q;

    x.resize(n);
    for (int i = 0; i < n; i++)
    {
        cin >> x[i];
    }
    build();

    vector<long long> res;
    while (q--)
    {
        int query_type;
        cin >> query_type;

        if (query_type == 1)
        {
            int k, u;
            cin >> k >> u;
            k--;
            update(1, 0, base - 1, k, n - 1, u - x[k]);
            x[k] = u;
        }
        else
        {
            int a, b;
            cin >> a >> b;
            a--;
            b--;
            long long max_prefix = query(1, 0, base - 1, a, b, 0);
            res.push_back(max(0LL, max_prefix - query(1, 0, base - 1, 0, a - 1, 0)));
        }
    }

    for (auto ans : res)
    {
        cout << ans << endl;
    }
}