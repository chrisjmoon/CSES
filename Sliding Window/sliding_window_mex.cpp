#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, k;
    cin >> n >> k;

    vector<int> x(n);
    unordered_map<int, set<int>> mp;
    unordered_map<int, int> freq;
    for (int i = 0; i < n; i++)
    {
        cin >> x[i];
    }

    for (int i = 0; i < k; i++)
    {
        freq[x[i]]++;
    }
    for (auto v : freq)
    {
        mp[v.second].insert(v.first);
    }
    for (int i = 0; i <= n; i++)
    {
        if (freq[i] == 0)
        {
            mp[0].insert(i);
        }
    }

    vector<int> ans = {*mp[0].begin()};
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

        ans.push_back(*mp[0].begin());
    }

    for (auto v : ans)
    {
        cout << v << " ";
    }
    cout << endl;
}