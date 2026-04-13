#include <bits/stdc++.h>
using namespace std;

long long MOD = 1e9 + 7;

long long sum(int i, vector<long long> &fenwick)
{
    if (i < 0)
    {
        return 0;
    }
    long long res = 0;
    while (i > 0)
    {
        res = (res + fenwick[i]) % MOD;
        i -= i & -i;
    }
    return res;
}

void update(int index, long long v, vector<long long> &fenwick)
{
    int n = fenwick.size();
    while (index < n)
    {
        fenwick[index] = (fenwick[index] + v) % MOD;
        index += (index & -index);
    }
}

int main()
{
    int n;
    cin >> n;
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
        x[i] = lower_bound(cc.begin(), cc.end(), x[i]) - cc.begin();
    }

    long long MOD = 1e9 + 7;
    int m = cc.size();
    // dp[i] - number of subsequences ending on i
    vector<long long> dp(n);
    vector<long long> fenwick(m + 1);

    for (int i = 0; i < n; i++)
    {
        dp[i] = (1 + sum(x[i], fenwick)) % MOD;
        update(x[i] + 1, dp[i], fenwick);
    }

    long long res = 0;
    for (int i = 0; i < n; i++)
    {
        res = (res + dp[i]) % MOD;
    }

    cout << res << endl;
}