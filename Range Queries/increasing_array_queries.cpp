#include <bits/stdc++.h>
using namespace std;

// merging
// binary search -> [l, r] in right node needs to be raised to at least x
// query sum for [l, r]

struct Node
{
    vector<int> increasing;   // monotonic increasing stack
    vector<int> indices;      // indices of the monotonic stack
    vector<long long> suffix; // suffix sum for monotonic
    long long sum;
};

vector<int> x;
vector<Node> t;
vector<long long> ps;
int base = 1;
int MAX = 1e9 + 5;

void merge(int node, int i, int j)
{
    if (i == j)
    {
        t[node].increasing = vector<int>{x[i]};
        t[node].indices = vector<int>{i};
        t[node].suffix = vector<long long>{0};
        t[node].sum = x[i];
        return;
    }

    int k = (i + j) / 2;
    merge(2 * node, i, k);
    merge(2 * node + 1, k + 1, j);

    t[node].sum = t[2 * node].sum + t[2 * node + 1].sum;
    vector<int> &increasing = t[node].increasing;
    vector<int> &indices = t[node].indices;
    vector<long long> &suffix = t[node].suffix;

    int left_max = t[2 * node].increasing.back();
    int right_index = upper_bound(t[2 * node + 1].increasing.begin(),
                                  t[2 * node + 1].increasing.end(), left_max) -
                      t[2 * node + 1].increasing.begin();
    increasing.insert(increasing.end(), t[2 * node].increasing.begin(),
                      t[2 * node].increasing.end());
    increasing.insert(increasing.end(), t[2 * node + 1].increasing.begin() + right_index,
                      t[2 * node + 1].increasing.end());
    indices.insert(indices.end(), t[2 * node].indices.begin(), t[2 * node].indices.end());
    indices.insert(indices.end(), t[2 * node + 1].indices.begin() + right_index,
                   t[2 * node + 1].indices.end());

    // build suffix
    long long s = 0;
    suffix.resize(increasing.size());
    for (int e = increasing.size() - 1; e >= 0; e--)
    {
        if (e == increasing.size() - 1)
        {
            s += 1LL * increasing[e] * (j - indices[e] + 1);
            s -= (ps[j + 1] - ps[indices[e]]);
        }
        else
        {
            s += 1LL * increasing[e] * (indices[e + 1] - indices[e]);
            s -= (ps[indices[e + 1]] - ps[indices[e]]);
        }
        suffix[e] = s;
    }
}

void build()
{
    int n = x.size();
    while (base < n)
    {
        base *= 2;
    }

    x.resize(base, MAX);
    t.resize(2 * base);
    ps.resize(base + 1);
    long long s = 0;
    for (int i = 0; i < base; i++)
    {
        s += x[i];
        ps[i + 1] = s;
    }
    merge(1, 0, base - 1);
}

// returns number of operations required and max in the range
pair<long long, int> query(int node, int i, int j, int e, int f, int target)
{
    if (j < e || i > f)
    {
        return pair<long long, int>{0, target};
    }
    if (e <= i && j <= f)
    {
        int index = lower_bound(t[node].increasing.begin(), t[node].increasing.end(), target) -
                    t[node].increasing.begin();
        int raise_right;
        if (index == t[node].increasing.size())
        {
            raise_right = j + 1;
        }
        else
        {
            raise_right = t[node].indices[index];
        }
        long long pre_raise_sum = ps[raise_right] - ps[i];
        long long res = 1LL * target * (raise_right - i) - pre_raise_sum;
        if (index != t[node].increasing.size())
        {
            res += t[node].suffix[index];
        }

        return pair<long long, int>(res, max(target, t[node].increasing.back()));
    }

    int k = (i + j) / 2;
    pair<long long, int> left = query(2 * node, i, k, e, f, target);
    pair<long long, int> right = query(2 * node + 1, k + 1, j, e, f, left.second);
    return pair<long long, int>(left.first + right.first, right.second);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

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
        int a, b;
        cin >> a >> b;
        a--;
        b--;

        res.push_back(query(1, 0, base - 1, a, b, 0).first);
    }

    for (auto v : res)
    {
        cout << v << '\n';
    }
}