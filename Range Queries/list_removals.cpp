#include <bits/stdc++.h>
using namespace std;

vector<int> indices;
vector<int> tree;
vector<int> lazy;
int base = 1;

void build()
{
    int n = indices.size();
    while (base < n)
    {
        base *= 2;
    }

    tree.resize(2 * base);
    lazy.resize(2 * base);
    for (int i = 0; i < n; i++)
    {
        tree[base + i] = indices[i];
    }
    for (int i = base - 1; i >= 0; i--)
    {
        tree[i] = max(tree[2 * i], tree[2 * i + 1]);
    }
}

// returns the leftmost occurence of index
int query(int v, int i, int j, int target)
{
    if (i == j)
    {
        return i;
    }

    int k = (i + j) / 2;
    target -= lazy[v];
    if (tree[2 * v] >= target)
    {
        return query(2 * v, i, k, target);
    }
    else
    {
        return query(2 * v + 1, k + 1, j, target);
    }
}

void update(int v, int i, int j, int e, int f, int delta)
{
    if (e > f)
    {
        return;
    }
    if (i == e && j == f)
    {
        tree[v] += delta;
        lazy[v] += delta;
        return;
    }

    int k = (i + j) / 2;
    update(2 * v, i, k, e, min(k, f), delta);
    update(2 * v + 1, k + 1, j, max(k + 1, e), f, delta);
    tree[v] = max(tree[2 * v], tree[2 * v + 1]) + lazy[v];
}

int main()
{
    int n;
    cin >> n;

    indices.resize(n);
    iota(indices.begin(), indices.end(), 0);
    vector<int> x(n);
    for (int i = 0; i < n; i++)
    {
        cin >> x[i];
    }

    build();
    vector<int> res;
    for (int i = 0; i < n; i++)
    {
        int r;
        cin >> r;
        r--;

        int pos = query(1, 0, base - 1, r);
        res.push_back(x[pos]);
        update(1, 0, base - 1, pos, n - 1, -1);
    }

    for (auto v : res)
    {
        cout << v << " ";
    }
    cout << endl;
}