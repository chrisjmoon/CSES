#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, k;
    cin >> n >> k;

    vector<int> x(n);
    for (int i = 0; i < n; i++)
    {
        cin >> x[i];
    }

    set<int> left, right;
    vector<int> w;
    for (int i = 0; i < k; i++)
    {
        w.push_back(x[i]);
    }
    sort(w.begin(), w.end());
    for (int i = 0; i < k / 2; i++)
    {
        left.insert(w[i]);
    }
    for (int i = k / 2; i < k; i++)
    {
        right.insert(w[i]);
    }

    vector<int> ans = {*left.rbegin()};
    for (int i = k; i < n; i++)
    {
        cout << "left" << endl;
        for (auto v : left)
        {
            cout << v << " ";
        }
        cout << endl;
        cout << "right" << endl;
        for (auto v : right)
        {
            cout << v << " ";
        }
        cout << endl;

        // remove i - k
        if (x[i - k] <= *left.rbegin())
        {
            left.erase(x[i - k]);
            left.insert(*right.begin());
            right.erase(*right.begin());
        }
        else
        {
            right.erase(x[i - k]);
            right.insert(*left.rbegin());
            left.erase(*left.rbegin());
        }

        // add i
        if (x[i] <= *left.rbegin())
        {
            left.insert(x[i]);
            right.insert(*left.rbegin());
            left.erase(*left.rbegin());
        }
        else
        {
            right.insert(x[i]);
            left.insert(*right.begin());
            right.erase(*right.begin());
        }

        ans.push_back(*left.rbegin());
    }

    for (auto v : ans)
    {
        cout << v << " ";
    }
    cout << endl;
}