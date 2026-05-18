#include <bits/stdc++.h>
using namespace std;

vector<int> x;
vector<long long> tree;
int base = 1;

void build()
{
    int n = x.size();
    while (base < n)
    {
        base *= 2;
    }

    tree.resize(2 * base);
    for (int i = 0; i < n; i++)
    {
        tree[base + i] = x[i];
    }

    for (int i = base - 1; i >= 0; i--)
    {
        tree[i] = tree[2 * i] + tree[2 * i + 1];
    }
}

long long query(int node, int i, int j, int e, int f)
{
    if (i == e && j == f)
    {
        return tree[node];
    }

    int k = (i + j) / 2;
    if (f <= k)
    {
        return query(2 * node, i, k, e, f);
    }
    else if (k < e)
    {
        return query(2 * node + 1, k + 1, j, e, f);
    }
    else
    {
        return query(2 * node, i, k, e, min(k, f)) +
               query(2 * node + 1, k + 1, j, max(k + 1, e), f);
    }
}

void update(int i, int delta)
{
    int j = base + i;
    while (j > 0)
    {
        tree[j] += delta;
        j /= 2;
    }
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

        if (query_type == 2)
        {
            int i, j;
            cin >> i >> j;
            i--;
            j--;

            res.push_back(query(1, 0, base - 1, i, j));
        }
        else
        {
            int k, u;
            cin >> k >> u;
            k--;
            update(k, u - x[k]);
            x[k] = u;
        }
    }

    for (auto ans : res)
    {
        cout << ans << endl;
    }
}