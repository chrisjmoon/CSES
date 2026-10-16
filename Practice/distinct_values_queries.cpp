#include <bits/stdc++.h>

using namespace std;
#define ll long long

vector<int> fenwick;

void update(int x, int value)
{
    x++;
    int n = fenwick.size();
    while (x < n)
    {
        fenwick[x] += value;
        x += (x & -x);
    }
}

int query(int l, int r)
{
    // determine the sum of values in the range [l, r]
    int res{};
    r++;
    while (r > 0)
    {
        res += fenwick[r];
        r -= (r & -r);
    }

    while (l > 0)
    {
        res -= fenwick[l];
        l -= (l & -l);
    }

    return res;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    vector<ll> a(n);
    vector<ll> cc;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
        cc.push_back(a[i]);
    }

    sort(cc.begin(), cc.end());
    cc.erase(unique(cc.begin(), cc.end()), cc.end());

    fenwick.resize(n + 1);

    vector<pair<int, pair<int, int>>> queries;
    for (int i = 0; i < q; i++)
    {
        int x, y;
        cin >> x >> y;
        x--;
        y--;
        queries.emplace_back(i, pair<int, int>(x, y));
    }

    int m = cc.size();
    vector<int> last_seen_index(m, -1);
    vector<int> prev_index(n, -1); // last_index[i] is the previous index of the value a[i]; -1 if unseen before i
    for (int i = 0; i < n; i++)
    {
        int j = lower_bound(cc.begin(), cc.end(), a[i]) - cc.begin();
        prev_index[i] = last_seen_index[j];
        last_seen_index[j] = i;
    }

    sort(queries.begin(), queries.end(), [](const auto &x, const auto &y)
         { return x.second.second < y.second.second; }); // sort in order of increasing right end

    int current_right{-1};
    vector<int> res(q);
    for (int i = 0; i < queries.size(); i++)
    {
        while (current_right < queries[i].second.second)
        {
            // introduce new canonical indices into scope
            current_right++;
            update(current_right, 1);
            if (prev_index[current_right] != -1)
            {
                update(prev_index[current_right], -1); // remove count
            }
        }

        res[queries[i].first] = query(queries[i].second.first, queries[i].second.second);
    }

    for (auto v : res)
    {
        cout << v << '\n';
    }
}