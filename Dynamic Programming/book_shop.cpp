#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, x;
    cin >> n >> x;
    vector<int> c(n), p(n);
    for (int i = 0; i < n; i++)
    {
        cin >> c[i];
    }
    for (int i = 0; i < n; i++)
    {
        cin >> p[i];
    }

    vector<int> dp(x + 1, 0);
    for (int i = 0; i < n; i++)
    {
        for (int j = x; j >= 0; j--)
        {
            if (c[i] > j)
            {
                continue;
            }
            dp[j] = max(dp[j], dp[j - c[i]] + p[i]);
        }
    }
    cout << *max_element(dp.begin(), dp.end()) << endl;
}