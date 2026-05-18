#include <bits/stdc++.h>
using namespace std;

vector<int> x;
vector<vector<long long>> t; // 0: sum, 1: max prefix, 2: max suffix, 3: max subarray sum
int base = 1;

void merge(int node)
{
    long long sum = t[2 * node][0] + t[2 * node + 1][0];
    // max prefix is either left max prefix or left sum + right max prefix
    long long max_prefix = max(t[2 * node][1], t[2 * node][0] + t[2 * node + 1][1]);
    long long max_suffix = max(t[2 * node + 1][2], t[2 * node + 1][0] + t[2 * node][2]);
    long long max_subarray = max(t[2 * node][3], t[2 * node + 1][3]);
    max_subarray = max(max_subarray, t[2 * node][2] + t[2 * node + 1][1]);

    t[node] = vector<long long>{sum, max_prefix, max_suffix, max_subarray};
}

void build()
{
    int n = x.size();
    while (base < n)
    {
        base *= 2;
    }

    x.resize(base);
    t.resize(2 * base);
    for (int i = 0; i < base; i++)
    {
        t[base + i] = vector<long long>{x[i], x[i], x[i], x[i]};
    }
    for (int i = base - 1; i > 0; i--)
    {
        merge(i);
    }
}

void update(int node, int i, int j, int index, int v)
{
    if (i == j)
    {
        t[node] = vector<long long>{v, v, v, v};
        return;
    }

    int k = (i + j) / 2;
    if (index <= k)
    {
        update(2 * node, i, k, index, v);
    }
    else
    {
        update(2 * node + 1, k + 1, j, index, v);
    }

    merge(node);
}

int main()
{
    int n, m;
    cin >> n >> m;

    x.resize(n);
    for (int i = 0; i < n; i++)
    {
        cin >> x[i];
    }

    build();
    vector<long long> res;
    for (int i = 0; i < m; i++)
    {
        int index, v;
        cin >> index >> v;
        index--;

        update(1, 0, base - 1, index, v);
        res.push_back(max(t[1][3], 0LL));
    }

    for (auto v : res)
    {
        cout << v << endl;
    }
}