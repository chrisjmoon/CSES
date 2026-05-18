#include <bits/stdc++.h>
using namespace std;

vector<int> h;
vector<int> tree;
int base = 1;

void build()
{
    int n = h.size();
    while (base < n)
    {
        base *= 2;
    }

    tree.resize(2 * base);
    for (int i = 0; i < n; i++)
    {
        tree[base + i] = h[i];
    }

    for (int i = base - 1; i >= 0; i--)
    {
        tree[i] = max(tree[2 * i], tree[2 * i + 1]);
    }
}

int query(int v, int i, int j, int target)
{
    if (target > tree[v])
    {
        return -1;
    }

    if (i == j)
    {
        return i;
    }

    int k = (i + j) / 2;
    if (tree[2 * v] >= target)
    {
        return query(2 * v, i, k, target);
    }
    else
    {
        return query(2 * v + 1, k + 1, j, target);
    }
}

void update(int i, int delta)
{
    tree[base + i] += delta;
    int j = (base + i) / 2;
    while (j > 0)
    {
        tree[j] = max(tree[2 * j], tree[2 * j + 1]);
        j /= 2;
    }
}

int main()
{
    int n, m;
    cin >> n >> m;

    h.resize(n);
    for (int i = 0; i < n; i++)
    {
        cin >> h[i];
    }

    build();
    vector<int> res;
    for (int i = 0; i < m; i++)
    {
        int g;
        cin >> g;

        int hotel = query(1, 0, base - 1, g);
        res.push_back(hotel + 1);
        update(hotel, -g);
    }

    for (auto v : res)
    {
        cout << v << " ";
    }
    cout << endl;
}