#include <bits/stdc++.h>
using namespace std;

long long MOD = 1e9 + 7;

int main()
{
    int n;
    cin >> n;

    // suppose we have n children already deranged (haha)
    // we introduce child n + 1
    // to create a derangement, all we need to do is gift that child's gift to someone else
    // essentially a swap
    // child x and child n + 1 swap their gifts
    // how many arrangements of the first n gifts (without the gift child x had) are there
    // among the other n - 1 children
    // say child x had gift y
    // among the n - 1 children, n - 2 of their gifts are there, but child y does not have their
    // gift d(n - 1) undercounts permutations for which y does not have gift x so we add d(n - 2)
    // for the number of arrangements where child x has gift y is d(n - 1) + d(n - 2)
    // gift child i gift n + 1
    // gift child n + 1 some gift j
    // need to count for this configuration, the number of ways we can distribute the first n gifts
    // (without gift j) to the n children without child i d(n - 1) + d(n - 2) how many
    // configurations of i, j are there? n^2

    vector<long long> dp(n + 1);
    dp[1] = 0;
    dp[2] = 1;
    dp[3] = 2; // bca, cab

    for (int i = 4; i <= n; i++)
    {
        long long r = ((i - 1) * (i - 1)) % MOD;
        r = (r * dp[i - 2]) % MOD;
        r = (r * dp[i - 3]) % MOD;
        dp[i] = r;
    }

    cout << dp[n] << endl;
}