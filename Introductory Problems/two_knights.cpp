#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;

    // x
    // - - x
    // - x

    // - x
    // - - - x
    // x - x

    // - - x
    // x - - - - x
    // - x - x - -

    vector<long long> dp = {0, 6, 28, 96, 252, 550};

    for (long long i = dp.size() + 1; i <= n; i++)
    {
        long long x = dp.back();
        // from x we can calculate the number of bad pairs
        x = (i - 1) * (i - 1) * ((i - 1) * (i - 1) - 1) / 2 - x;
        // add bad pairs
        x += ((i - 4) * 4 + 10) * 2 - 4;
        dp.push_back(i * i * (i * i - 1) / 2 - x);
    }

    for (int i = 0; i < n; i++)
    {
        cout << dp[i] << endl;
    }
}