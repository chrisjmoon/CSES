#include <bits/stdc++.h>
using namespace std;

vector<long long> x;

struct Node
{
    long long sum;
    long long max_prefix;
    long long max_suffix;
    long long max_subarray_sum;
};

vector<Node> t;
int base = 1;

Node merge(Node l, Node r)
{
    Node node;
    node.sum = l.sum + r.sum;
    node.max_prefix = max(l.max_prefix, l.sum + r.max_prefix);
    node.max_suffix = max(r.max_suffix, r.sum + l.max_suffix);
    node.max_subarray_sum = max(l.max_subarray_sum, r.max_subarray_sum);
    node.max_subarray_sum = max(node.max_subarray_sum, l.max_suffix + r.max_prefix);

    return node;
}

void build()
{
    int n = x.size();
    while (base < n)
    {
        base *= 2;
    }

    t.resize(2 * base);
    for (int i = 0; i < n; i++)
    {
        t[base + i].sum = x[i];
        t[base + i].max_prefix = x[i];
        t[base + i].max_suffix = x[i];
        t[base + i].max_subarray_sum = x[i];
    }

    for (int i = base - 1; i > 0; i--)
    {
        t[i] = merge(t[2 * i], t[2 * i + 1]);
    }
}

Node query(int node, int i, int j, int e, int f)
{
    if (j < e || i > f)
    {
        return Node();
    }

    if (e <= i && j <= f)
    {
        return t[node];
    }

    int k = (i + j) / 2;
    Node left_node = query(2 * node, i, k, e, f);
    Node right_node = query(2 * node + 1, k + 1, j, e, f);
    return merge(left_node, right_node);
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
        int a, b;
        cin >> a >> b;
        a--;
        b--;

        Node q = query(1, 0, base - 1, a, b);
        res.push_back(max(0LL, q.max_subarray_sum));
    }

    for (auto v : res)
    {
        cout << v << endl;
    }
}