#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, k;
    cin >> n >> k;

    vector<long long> x(n);
    vector<long long> cc;
    for (int i = 0; i < n; i++)
    {
        cin >> x[i];
        cc.push_back(x[i]);
    }

    sort(cc.begin(), cc.end());
    cc.erase(unique(cc.begin(), cc.end()), cc.end());
    int m = cc.size();
    vector<int> count(m);
    int w = 0;
    for (int i = 0; i < k; i++)
    {
        int j = lower_bound(cc.begin(), cc.end(), x[i]) - cc.begin();
        count[j]++;
        if (count[j] == 1)
        {
            w++;
            ;
        }
    }

    vector<int> res = {w};
    for (int i = k; i < n; i++)
    {
        // remove i - k
        int j = lower_bound(cc.begin(), cc.end(), x[i - k]) - cc.begin();
        count[j]--;
        if (count[j] == 0)
        {
            w--;
        }

        // add in i
        j = lower_bound(cc.begin(), cc.end(), x[i]) - cc.begin();
        count[j]++;
        if (count[j] == 1)
        {
            w++;
        }

        res.push_back(w);
    }

    for (auto v : res)
    {
        cout << v << " ";
    }
    cout << endl;
}