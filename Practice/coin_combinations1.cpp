#include <bits/stdc++.h>

constexpr long long MOD = 1'000'000'007;

using namespace std;

int main()
{
    int n;
    long long x;
    cin >> n >> x;

    vector<long long> coins(n);
    vector<long long> dp(x + 1);

    for (int i = 0; i < n; i++)
    {
        cin >> coins[i];
    }

    dp[0] = 1;

    for (long long target{1}; target <= x; target++)
    {
        for (long long coin : coins)
        {
            if (coin <= target)
            {
                dp[target] = (dp[target] + dp[target - coin]) % MOD;
            }
        }
    }

    cout << dp[x] << endl;
}