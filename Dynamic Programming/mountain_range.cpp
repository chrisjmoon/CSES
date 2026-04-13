#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<int> h(n);
    for (int i = 0; i < n; i++)
    {
        cin >> h[i];
    }

    vector<int> l(n, -1), r(n, -1), a(n, 1);
    stack<int> s;
    for (int i = 0; i < n; i++)
    {
        while (!s.empty() && h[s.top()] <= h[i])
        {
            s.pop();
        }
        if (!s.empty())
        {
            l[i] = s.top();
        }
        s.push(i);
    }

    s = stack<int>();
    for (int i = n - 1; i >= 0; i--)
    {
        while (!s.empty() && h[s.top()] <= h[i])
        {
            s.pop();
        }
        if (!s.empty())
        {
            r[i] = s.top();
        }
        s.push(i);
    }

    vector<pair<int, int>> h_;
    for (int i = 0; i < n; i++)
    {
        h_.emplace_back(h[i], i);
    }
    sort(h_.rbegin(), h_.rend());
    for (auto p : h_)
    {
        if (l[p.second] != -1)
        {
            a[p.second] = max(a[p.second], a[l[p.second]] + 1);
        }
        if (r[p.second] != -1)
        {
            a[p.second] = max(a[p.second], a[r[p.second]] + 1);
        }
    }

    cout << *max_element(a.begin(), a.end()) << endl;
}