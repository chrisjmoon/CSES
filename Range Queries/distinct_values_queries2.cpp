#include <bits/stdc++.h>
using namespace std;

vector<int> next_index;
vector<int> t;
int base = 1;
int MAX = 1e6;

void build()
{
    int n = next_index.size();
    while (base < n)
    {
        base *= 2;
    }

    t.resize(2 * base);
    next_index.resize(base, n);
    for (int i = 0; i < base; i++)
    {
        t[base + i] = next_index[i];
    }
    for (int i = base - 1; i >= 0; i--)
    {
        t[i] = min(t[2 * i], t[2 * i + 1]);
    }
}

int query(int node, int i, int j, int e, int f)
{
    if (j < e || i > f)
    {
        return MAX;
    }

    if (e <= i && j <= f)
    {
        return t[node];
    }

    int k = (i + j) / 2;
    return min(query(2 * node, i, k, e, f), query(2 * node + 1, k + 1, j, e, f));
}

void update(int node, int i, int j, int e, int val)
{
    if (i == j)
    {
        t[node] = val;
        return;
    }

    int k = (i + j) / 2;
    if (e <= k)
    {
        update(2 * node, i, k, e, val);
    }
    else
    {
        update(2 * node + 1, k + 1, j, e, val);
    }
    t[node] = min(t[2 * node], t[2 * node + 1]);
}

int main()
{
    int n, q;
    cin >> n >> q;

    // next[i]: the index of the next occurrence of x[i]
    // segment tree on next[i] gets minimum value of next[i] in the range
    // if min is larger than R for query [L, R], then all values are distinct
    // suppose we update index k to u
    // let i be the index of the previous occurrence of nums[k] (before update)
    // need to update next[i]
    // let j be the index of the previous occurrence of u
    // need to update next[j]

    vector<int> cc;
    vector<int> x(n);
    for (int i = 0; i < n; i++)
    {
        cin >> x[i];
        cc.push_back(x[i]);
    }
    vector<pair<int, pair<int, int>>> queries;
    for (int i = 0; i < q; i++)
    {
        int query_type;
        cin >> query_type;
        if (query_type == 1)
        {
            int k, u;
            cin >> k >> u;
            k--;
            cc.push_back(u);
            queries.emplace_back(query_type, pair<int, int>(k, u));
        }
        else
        {
            int a, b;
            cin >> a >> b;
            a--;
            b--;
            queries.emplace_back(query_type, pair<int, int>(a, b));
        }
    }

    sort(cc.begin(), cc.end());
    cc.erase(unique(cc.begin(), cc.end()), cc.end());
    int m = cc.size();

    vector<set<int>> indices(m);
    for (int i = 0; i < m; i++)
    {
        indices[i].insert(n);
    }
    // compress
    for (int i = 0; i < n; i++)
    {
        int j = lower_bound(cc.begin(), cc.end(), x[i]) - cc.begin();
        x[i] = j;
        indices[j].insert(i);
    }
    for (int i = 0; i < q; i++)
    {
        if (queries[i].first == 1)
        {
            int u = queries[i].second.second;
            int j = lower_bound(cc.begin(), cc.end(), u) - cc.begin();
            queries[i].second.second = j;
        }
    }

    vector<int> last_index(m, -1);
    next_index.resize(n, n);
    for (int i = n - 1; i >= 0; i--)
    {
        if (last_index[x[i]] != -1)
        {
            next_index[i] = last_index[x[i]];
        }
        last_index[x[i]] = i;
    }

    // update index k to u
    // let v be the value of x[k] before the update
    // let w be the value of next_index[k] before the update
    // 1. update next_index[k] to the next occurrence of u
    // 2. update next_index[k'] to k where k' is a previous occurrence of u
    // 3. update next_index[k''] to w where k'' is a previous occurrence of v

    vector<bool> res;
    build();
    for (int i = 0; i < q; i++)
    {
        int query_type = queries[i].first;
        if (query_type == 2)
        {
            int a = queries[i].second.first;
            int b = queries[i].second.second;
            int min_index = query(1, 0, base - 1, a, b);
            res.push_back(min_index > b);
        }
        else
        {
            int k = queries[i].second.first;
            int u = queries[i].second.second;
            int v = x[k];
            if (u == v)
            {
                continue;
            }

            // find previous occurrence of u before k
            // find occurrence of u after k
            // find occurrence of v before k
            // find occurrence of v after k

            auto it0 = indices[u].lower_bound(k);
            auto it1 = indices[u].upper_bound(k);
            auto it2 = indices[v].lower_bound(k);
            auto it3 = indices[v].upper_bound(k);
            if (it0 != indices[u].begin())
            {
                it0--;
                update(1, 0, base - 1, *it0, k);
            }
            update(1, 0, base - 1, k, *it1);
            if (it2 != indices[v].begin())
            {
                it2--;
                update(1, 0, base - 1, *it2, *it3);
            }
            indices[u].insert(k);
            indices[v].erase(k);
            x[k] = u;
        }
    }

    for (bool v : res)
    {
        cout << (v ? "YES" : "NO") << endl;
    }
}