#include <bits/stdc++.h>
using namespace std;

// generates valid masks that can appear below n bits of 0
vector<int> next_valid_from_zero_group(int n)
{
    vector<int> res;
    for (int i = 0; i < (1 << n); i++)
    {
        int gap = 0;
        bool bad_gap = false;
        for (int j = 0; j < n; j++)
        {
            if ((1 << j & i))
            {
                if (gap % 2)
                {
                    bad_gap = true;
                    break;
                }
                else
                {
                    gap = 0;
                }
            }
            else
            {
                gap++;
            }
        }
        if (gap % 2)
        {
            bad_gap = true;
        }
        if (!bad_gap)
        {
            res.push_back(i);
        }
    }

    return res;
}

// generates valid masks that can appear after mask a
vector<int> get_next_valid_masks(int a, int n)
{
    vector<int> res = {0};
    int i = 0;
    while (i < n)
    {
        if (!(1 << i & a))
        {
            int j = i;
            while (j < n && !(1 << j & a))
            {
                j++;
            }
            vector<int> nv = next_valid_from_zero_group(j - i);
            vector<int> nr;
            for (auto r : res)
            {
                for (auto v : nv)
                {
                    nr.push_back(r | (v << i));
                }
            }
            res = nr;
            i = j;
        }
        else
        {
            i++;
        }
    }

    return res;
}

int main()
{
    int n, m;
    cin >> n >> m; // n <= 10, m <= 1000

    long long MOD = 1e9 + 7;
    vector<vector<long long>> dp(m + 1, vector<long long>((1 << n), 0));

    vector<vector<int>> valid(1 << n); // holds valid transitions from indexed row
    for (int i = 0; i < (1 << n); i++)
    {
        valid[i] = get_next_valid_masks(i, n);
    }

    dp[0][0] = 1;
    for (int i = 0; i < m; i++)
    {
        for (int mask = 0; mask < (1 << n); mask++)
        {
            if (dp[i][mask] == 0)
            {
                continue;
            }

            for (auto v : valid[mask])
            {
                dp[i + 1][v] = (dp[i + 1][v] + dp[i][mask]) % MOD;
            }
        }
    }

    cout << dp[m][0] % MOD << endl;
}