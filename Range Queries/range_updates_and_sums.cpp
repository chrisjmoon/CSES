#include <bits/stdc++.h>
using namespace std;

int q;
vector<int> x;
vector<long long> t;
vector<long long> lazy_sum;
vector<long long> lazy_set;
int base = 1;

void build()
{
    int n = x.size();
    while (base < n)
    {
        base *= 2;
    }

    t.resize(2 * base);
    lazy_sum.resize(2 * base);
    lazy_set.resize(2 * base);

    for (int i = 0; i < n; i++)
    {
        t[base + i] = x[i];
    }
    for (int i = base - 1; i > 0; i--)
    {
        t[i] = t[2 * i] + t[2 * i + 1];
    }
}

void push_lazy_sum(int node, int i, int j)
{
    if (lazy_sum[node] == 0)
    {
        return;
    }
    long long val = lazy_sum[node];
    int k = (i + j) / 2;
    t[2 * node] += val * (k - i + 1);
    t[2 * node + 1] += val * (j - k);
    lazy_sum[2 * node] += val;
    lazy_sum[2 * node + 1] += val;
    lazy_sum[node] = 0;
}

void push_lazy_set(int node, int i, int j)
{
    if (lazy_set[node] == 0)
    {
        return;
    }
    long long val = lazy_set[node];
    int k = (i + j) / 2;
    t[2 * node] = val * (k - i + 1);
    t[2 * node + 1] = val * (j - k);
    lazy_set[2 * node] = val;
    lazy_sum[2 * node] = 0;
    lazy_set[2 * node + 1] = val;
    lazy_sum[2 * node + 1] = 0;
    lazy_set[node] = 0;
}

void push(int node, int i, int j)
{
    push_lazy_set(node, i, j);
    push_lazy_sum(node, i, j);
}

// when update of type 2 occurs, we set update_sum for node to be 0
// when update of type 1 occurs, we increment update_sum
long long query(int node, int i, int j, int e, int f)
{
    if (j < e || i > f)
    {
        return 0;
    }
    if (e <= i && j <= f)
    {
        return t[node];
    }

    push(node, i, j);
    int k = (i + j) / 2;
    return query(2 * node, i, k, e, f) + query(2 * node + 1, k + 1, j, e, f);
}

// range add
void update1(int node, int i, int j, int e, int f, long long val)
{
    if (j < e || i > f)
    {
        return;
    }
    if (e <= i && j <= f)
    {
        lazy_sum[node] += val;
        t[node] += val * (j - i + 1);
        return;
    }

    push(node, i, j);
    int k = (i + j) / 2;
    update1(2 * node, i, k, e, f, val);
    update1(2 * node + 1, k + 1, j, e, f, val);
    t[node] = t[2 * node] + t[2 * node + 1];
}

// range assign
void update2(int node, int i, int j, int e, int f, long long val)
{
    if (j < e || i > f)
    {
        return;
    }
    if (e <= i && j <= f)
    {
        lazy_set[node] = val;
        lazy_sum[node] = 0;
        t[node] = val * (j - i + 1);
        return;
    }

    // can think of pushing such that when range overlaps node, we don't have to calculate?
    push(node, i, j);
    int k = (i + j) / 2;
    update2(2 * node, i, k, e, f, val);
    update2(2 * node + 1, k + 1, j, e, f, val);
    t[node] = t[2 * node] + t[2 * node + 1];
}

int main()
{
    int n;
    cin >> n >> q;

    x.resize(n);
    for (int i = 0; i < n; i++)
    {
        cin >> x[i];
    }

    build();
    vector<long long> res;
    for (int i = 0; i < q; i++)
    {
        int query_type;
        cin >> query_type;
        if (query_type == 1)
        {
            int a, b, x;
            cin >> a >> b >> x;
            a--;
            b--;
            update1(1, 0, base - 1, a, b, x);
        }
        else if (query_type == 2)
        {
            int a, b, x;
            cin >> a >> b >> x;
            a--;
            b--;
            update2(1, 0, base - 1, a, b, x);
        }
        else
        {
            int a, b;
            cin >> a >> b;
            a--;
            b--;
            res.push_back(query(1, 0, base - 1, a, b));
        }
    }

    for (auto v : res)
    {
        cout << v << endl;
    }
}