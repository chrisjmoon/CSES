#include <bits/stdc++.h>
using namespace std;

vector<int> freq;
vector<long long> ft;

void add(int i, int delta)
{
    freq[i] += delta;
    i += 1;
    int n = ft.size();
    while (i < n)
    {
        ft[i] += delta;
        i += i & -i;
    }
}

// sum frequencies from 0 to i inclusive
long long query(int i)
{
    long long res = 0;
    i += 1;
    while (i > 0)
    {
        res += ft[i];
        i -= i & -i;
    }
    return res;
}

long long query_range(int i, int j)
{
    return query(j) - query(i - 1);
}

int main()
{
    int n, k;
    cin >> n >> k;

    vector<int> x(n);
    vector<int> cc;
    for (int i = 0; i < n; i++)
    {
        cin >> x[i];
        cc.push_back(x[i]);
    }

    sort(cc.begin(), cc.end());
    cc.erase(unique(cc.begin(), cc.end()), cc.end());
    for (int i = 0; i < n; i++)
    {
        int j = lower_bound(cc.begin(), cc.end(), x[i]) - cc.begin();
        x[i] = j;
    }

    int m = cc.size();
    freq.resize(m);
    ft.resize(m + 1);
    long long inversions = 0;
    for (int i = 0; i < k; i++)
    {
        add(x[i], 1);
        inversions += query_range(x[i] + 1, m - 1);
    }

    vector<long long> res = {inversions};
    for (int i = k; i < n; i++)
    {
        // remove i - k
        inversions -= (query(x[i - k]) - freq[x[i - k]]);
        add(x[i - k], -1);
        // add i
        inversions += query_range(x[i] + 1, m - 1);
        add(x[i], 1);
        res.push_back(inversions);
    }

    for (auto v : res)
    {
        cout << v << " ";
    }
    cout << endl;
}