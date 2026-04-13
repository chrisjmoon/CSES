#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, x;
    cin >> n >> x;
    vector<int> w(n);
    for (int i = 0; i < n; i++)
    {
        cin >> w[i];
    }

    vector<vector<long long>> buckets(n + 1);
    for (int i = 1; i < (1 << n); i++)
    {
        int bits = __builtin_popcount(i);
        buckets[bits].push_back(i);
    }

    vector<int> res(1 << n, n);
    vector<long long> rem(1 << n, x);
    res[0] = 0;
    rem[0] = 0;
    for (int i = 0; i < buckets[1].size(); i++)
    {
        res[buckets[1][i]] = 1;
        rem[buckets[1][i]] = w[__builtin_ctz(buckets[1][i])];
    }
    for (int i = 2; i <= n; i++)
    {
        for (int j = 0; j < buckets[i].size(); j++)
        {
            long long v = buckets[i][j];
            for (int k = 0; (1 << k) <= v; k++)
            {
                if (!((1 << k) & v))
                {
                    continue;
                }

                long long v_ = v ^ (1 << k);
                int min_rides;
                long long min_last_weight;
                if (rem[v_] + w[k] <= x)
                {
                    min_rides = res[v_];
                    min_last_weight = rem[v_] + w[k];
                }
                else
                {
                    min_rides = res[v_] + 1;
                    min_last_weight = w[k];
                }

                if (min_rides < res[v])
                {
                    res[v] = min_rides;
                    rem[v] = min_last_weight;
                }
                else if (min_rides == res[v])
                {
                    rem[v] = min(rem[v], min_last_weight);
                }
            }
        }
    }

    cout << res[(1 << n) - 1] << endl;
}