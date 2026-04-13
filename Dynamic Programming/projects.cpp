#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<int> cc; // coordinate compression
    vector<tuple<int, int, int>> intervals;
    int a, b, p;
    for (int i = 0; i < n; i++)
    {
        cin >> a >> b >> p;
        cc.push_back(a);
        cc.push_back(b);
        intervals.push_back(tuple<int, int, int>(a, b, p));
    }

    cc.erase(unique(cc.begin(), cc.end()), cc.end());
    sort(cc.begin(), cc.end());
    for (int i = 0; i < n; i++)
    {
        get<0>(intervals[i]) = lower_bound(cc.begin(), cc.end(), get<0>(intervals[i])) - cc.begin();
        get<1>(intervals[i]) = lower_bound(cc.begin(), cc.end(), get<1>(intervals[i])) - cc.begin();
    }

    sort(intervals.begin(), intervals.end(),
         [](const auto &x, const auto &y) { return get<1>(x) < get<1>(y); });
    int m = cc.size();
    int project_index = 0;
    vector<long long> dp(m + 1, 0);
    for (int i = 0; i < m; i++)
    {
        dp[i + 1] = dp[i];
        while (project_index < n && get<1>(intervals[project_index]) == i)
        {
            int start = get<0>(intervals[project_index]);
            int reward = get<2>(intervals[project_index]);
            dp[i + 1] = max(dp[i + 1], reward + dp[start]);
            project_index++;
        }
    }

    cout << *max_element(dp.begin(), dp.end()) << endl;
}