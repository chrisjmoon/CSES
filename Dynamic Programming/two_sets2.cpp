#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;

    long long s = 1LL * (n + 1) * n / 2;
    if (s % 2)
    {
        cout << 0 << endl;
        return 0;
    }

    long long t = s / 2;
    long long MOD = 1e9 + 7;
    vector<long long> dp(t + 1);
    dp[0] = 1;
    for (int i = 1; i < n; i++)
    {
        for (int j = t; j >= i; j--)
        {
            dp[j] = (dp[j] + dp[j - i]) % MOD;
        }
    }

    cout << dp[t] << endl;
}