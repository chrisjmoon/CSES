#include <bits/stdc++.h>

using namespace std;

long MOD = 1e9 + 7;

int main()
{
    int n;
    cin >> n;
    vector<long> dp(n + 1);

    dp[0] = 1;
    for (long i = 1; i <= n; i++)
    {
        for (int roll = 1; roll <= 6; roll++)
        {
            if (i >= roll)
            {
                dp[i] = (dp[i] + dp[i - roll]) % MOD;
            }
        }
    }

    cout << dp[n] << endl;
}