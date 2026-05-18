#include <bits/stdc++.h>
using namespace std;

using pi = pair<int, int>;
using ppi = pair<pi, pi>;

vector<int> fenwick;

void update(int i)
{
    i++;
    int n = fenwick.size();
    while (i < n)
    {
        fenwick[i]++;
        i += (i & -i);
    }
}

// prefix sum up to and including i
int query(int i)
{
    i++;
    int res = 0;
    while (i > 0)
    {
        res += fenwick[i];
        i -= (i & -i);
    }

    return res;
}

int main()
{
    int n, q;
    cin >> n >> q;

    vector<pi> x;
    for (int i = 0; i < n; i++)
    {
        int x_;
        cin >> x_;
        x.emplace_back(x_, i);
    }

    vector<pi> queries;
    vector<pair<int, pi>> qt; // <query threshold, <query index, subtract or add>>
    vector<int> res(q);
    for (int i = 0; i < q; i++)
    {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        a--;
        b--;

        queries.emplace_back(a, b);
        qt.emplace_back(c, pi(i, 0));
        qt.emplace_back(d + 1, pi(i, 1));
    }

    fenwick.resize(n + 1);
    sort(x.begin(), x.end());
    sort(qt.begin(), qt.end());

    // for each threshold (sorted), we update the fenwick tree with
    // all the elements that are < threshold
    int xi = 0;
    for (int i = 0; i < 2 * q; i++)
    {
        int threshold = qt[i].first;
        int qi = qt[i].second.first;
        int a = queries[qi].first;
        int b = queries[qi].second;
        while (xi < n && x[xi].first < threshold)
        {
            // update fenwick tree
            update(x[xi].second);
            xi++;
        }

        int amount = query(b) - query(a - 1);
        res[qi] += (qt[i].second.second ? 1 : -1) * amount;
    }

    for (auto v : res)
    {
        cout << v << endl;
    }
}