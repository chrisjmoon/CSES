#include <bits/stdc++.h>
using namespace std;

vector<int> x;
vector<int> fenwick;
int base = 1;

void update(int i, int delta)
{
    i += 1;
    int n = fenwick.size();
    while (i < n)
    {
        fenwick[i] += delta;
        i += (i & -i);
    }
}

int query(int a, int b)
{
    int res = 0;
    b += 1;
    int n = fenwick.size();
    while (b > 0)
    {
        res += fenwick[b];
        b -= (b & -b);
    }

    while (a > 0)
    {
        res -= fenwick[a];
        a -= (a & -a);
    }

    return res;
}

int main()
{
    int n, q;
    cin >> n >> q;

    x.resize(n);
    fenwick.resize(n + 1);
    vector<int> cc;
    for (int i = 0; i < n; i++)
    {
        cin >> x[i];
        cc.push_back(x[i]);
    }

    sort(cc.begin(), cc.end());
    cc.erase(unique(cc.begin(), cc.end()), cc.end());
    int m = cc.size();
    for (int i = 0; i < n; i++)
    {
        int j = lower_bound(cc.begin(), cc.end(), x[i]) - cc.begin();
        x[i] = j;
    }

    vector<pair<int, pair<int, int>>> queries;
    for (int i = 0; i < q; i++)
    {
        int a, b;
        cin >> a >> b;

        a--;
        b--;
        queries.push_back(pair<int, pair<int, int>>(i, pair<int, int>(a, b)));
    }

    sort(queries.begin(), queries.end(),
         [&](const auto &a, const auto &b) { return a.second.second < b.second.second; });
    int r = -1;
    vector<int> res(q);
    // last seen index
    vector<int> last_seen(m, -1);

    for (int i = 0; i < q; i++)
    {
        int query_index = queries[i].first;
        int a = queries[i].second.first;
        int b = queries[i].second.second;

        while (r < b)
        {
            int to_add = x[r + 1];
            if (last_seen[to_add] != -1)
            {
                update(last_seen[to_add], -1);
            }
            update(r + 1, 1);
            last_seen[to_add] = r + 1;
            r += 1;
        }

        res[query_index] = query(a, b);
    }

    for (auto v : res)
    {
        cout << v << endl;
    }
}