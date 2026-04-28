#include <bits/stdc++.h>
using namespace std;

long long MOD = 1e9 + 7;

int main()
{
    int n;
    cin >> n;

    if (n == 1)
    {
        cout << 0 << endl;
        return 0;
    }
    if (n == 2)
    {
        cout << 1 << endl;
        return 0;
    }

    // given fixed child i whom we give gift n
    // we can pretend child n owns gift i
    // d(n - 1) - derangements where child n does not receive gift i
    // d(n - 2)
    // (n - 1)(d(n -  1) + d(n - 2))

    vector<long long> dp(n + 1);
    dp[1] = 0;
    dp[2] = 1;
    for (int i = 3; i <= n; i++)
    {
        long long r = (dp[i - 1] + dp[i - 2]) % MOD;
        r = r * (i - 1) % MOD;
        dp[i] = r;
    }

    cout << dp[n] << endl;
}