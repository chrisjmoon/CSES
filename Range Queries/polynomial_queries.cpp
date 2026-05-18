#include <bits/stdc++.h>
using namespace std;

vector<int> x;
vector<long long> ls; // sum of starts that cover
vector<int> lc;
vector<long long> t;
int base = 1;

void build()
{
    int n = x.size();
    while (base < n)
    {
        base *= 2;
    }

    t.resize(2 * base);
    ls.resize(2 * base);
    lc.resize(2 * base);
    for (int i = 0; i < n; i++)
    {
        t[base + i] = x[i];
    }
    for (int i = base - 1; i > 0; i--)
    {
        t[i] = t[2 * i] + t[2 * i + 1];
    }
}

void push(int node, int i, int j)
{
    int k = (i + j) / 2;
    long long start_sum = ls[node];
    int count = lc[node];
    // push to left
    ls[2 * node] += start_sum;
    lc[2 * node] += count;
    t[2 * node] += (k - i + 1) * (1LL * count * (i + k + 2) - 2 * start_sum) / 2;

    // push to right
    ls[2 * node + 1] += start_sum;
    lc[2 * node + 1] += count;
    t[2 * node + 1] += (j - k) * (1LL * count * (j + k + 3) - 2 * start_sum) / 2;

    ls[node] = 0;
    lc[node] = 0;
}

long long query(int node, int i, int j, int start, int end)
{
    if (j < start || i > end)
    {
        return 0;
    }
    if (start <= i && j <= end)
    {
        return t[node];
    }

    push(node, i, j);
    int k = (i + j) / 2;
    return query(2 * node, i, k, start, end) + query(2 * node + 1, k + 1, j, start, end);
}

void update(int node, int i, int j, int start, int end)
{
    if (j < start || i > end)
    {
        return;
    }
    if (start <= i && j <= end)
    {
        ls[node] += start;
        lc[node] += 1;
        // sum from [(i - start + 1), (j - start + 1)]
        t[node] += 1LL * (j - i + 1) * (j + i + 2 - 2 * start) / 2;
        return;
    }

    push(node, i, j);
    int k = (i + j) / 2;
    update(2 * node, i, k, start, end);
    update(2 * node + 1, k + 1, j, start, end);
    t[node] = t[2 * node] + t[2 * node + 1];
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
    for (int i = 0; i < q; i++)
    {
        int query_type;
        cin >> query_type;

        if (query_type == 1)
        {
            int a, b;
            cin >> a >> b;
            a--;
            b--;
            update(1, 0, base - 1, a, b);
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