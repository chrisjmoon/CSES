#include <bits/stdc++.h>
using namespace std;
vector<long long> fenwick;
vector<int> bucket;

void update(int index, int delta)
{
    index++; // 1-indexed Fenwick tree
    int m = fenwick.size();
    while (index < m)
    {
        fenwick[index] += delta;
        index += (index & -index);
    }
}

// number of people with salaries in inclusive range [a, b]
long long query(int a, int b)
{
    long long res = 0;
    while (a > 0)
    {
        res -= fenwick[a];
        a -= (a & -a);
    }

    b++;
    while (b > 0)
    {
        res += fenwick[b];
        b -= (b & -b);
    }

    return res;
}

int main()
{
    int n, q;
    cin >> n >> q;

    vector<int> x(n);
    vector<int> cc;
    for (int i = 0; i < n; i++)
    {
        cin >> x[i];
        cc.push_back(x[i]);
    }

    vector<pair<int, pair<int, int>>> queries;
    for (int i = 0; i < q; i++)
    {
        char query_type;
        cin >> query_type;

        int a, b;
        cin >> a >> b;

        int query_int = 0;
        if (query_type == '!')
        {
            cc.push_back(b);
        }
        else
        {
            query_int = 1;
            cc.push_back(a);
            cc.push_back(b);
        }
        queries.push_back(pair<int, pair<int, int>>(query_int, pair<int, int>(a, b)));
    }

    sort(cc.begin(), cc.end());
    cc.erase(unique(cc.begin(), cc.end()), cc.end());
    int m = cc.size();
    bucket.resize(m);
    for (int i = 0; i < n; i++)
    {
        int j = lower_bound(cc.begin(), cc.end(), x[i]) - cc.begin();
        x[i] = j;
        bucket[j]++;
    }

    fenwick.resize(m + 1);
    for (int i = 0; i < m; i++)
    {
        update(i, bucket[i]);
    }

    // fenwick tree with prefix
    vector<long long> res;
    for (int i = 0; i < q; i++)
    {
        int query_int = queries[i].first;

        if (query_int == 0)
        {
            int k = queries[i].second.first;
            int new_salary = queries[i].second.second;
            new_salary = lower_bound(cc.begin(), cc.end(), new_salary) - cc.begin();
            k--;
            update(x[k], -1);
            update(new_salary, 1);
            x[k] = new_salary;
        }
        else
        {
            int a = queries[i].second.first;
            int b = queries[i].second.second;
            a = lower_bound(cc.begin(), cc.end(), a) - cc.begin();
            b = lower_bound(cc.begin(), cc.end(), b) - cc.begin();
            res.push_back(query(a, b));
        }
    }

    for (auto ans : res)
    {
        cout << ans << endl;
    }
}