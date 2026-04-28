#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, k;
    cin >> n >> k;
    vector<long long> x(n);
    for (int i = 0; i < n; i++)
    {
        cin >> x[i];
    }

    unordered_map<int, set<int>> mp;
    unordered_map<int, int> freq;
    for (int i = 0; i < k; i++)
    {
        freq[x[i]]++;
    }

    int mf = 0;
    for (auto v : freq)
    {
        mp[v.second].insert(v.first);
        mf = max(mf, v.second);
    }
    vector<int> ans = {*mp[mf].begin()};
    for (int i = k; i < n; i++)
    {

        // remove i - k
        mp[freq[x[i - k]]].erase(x[i - k]);
        mp[freq[x[i - k]] - 1].insert(x[i - k]);
        freq[x[i - k]]--;
        // add i
        mp[freq[x[i]]].erase(x[i]);
        mp[freq[x[i]] + 1].insert(x[i]);
        freq[x[i]]++;

        if (mp[mf + 1].size())
        {
            mf++;
        }
        else if (mp[mf].empty())
        {
            mf--;
        }

        ans.push_back(*mp[mf].begin());
    }

    for (auto v : ans)
    {
        cout << v << " ";
    }
    cout << endl;
}