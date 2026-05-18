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

// range update inclusive range [i, j] with +k
void update(int i, int j, int k)
{
    int node = base + i;
    while (node > 0)
    {
        tree[node] += k;
        node /= 2;
    }
    node = base + j + 1;
    while (node > 0)
    {
        tree[node] -= k;
        node /= 2;
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

        if (query_type == 1)
        {
            int i, j, u;
            cin >> i >> j >> u;
            i--;
            j--;
            update(i, j, u);
        }
        else
        {
            int i;
            cin >> i;
            i--;

            res.push_back(query(1, 0, base - 1, 0, i) + x[i]);
        }
    }

    for (auto ans : res)
    {
        cout << ans << endl;
    }
}