#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<int> x(n);
    for (int i = 0; i < n; i++)
    {
        cin >> x[i];
    }

    vector<bool> a(100001);
    a[0] = true;
    vector<int> res;
    for (int i = 0; i < n; i++)
    {
        for (int j = 100001; j >= x[i]; j--)
        {
            if (a[j - x[i]])
            {
                a[j] = true;
            }
        }
    }

    for (int i = 1; i < 100001; i++)
    {
        if (a[i])
        {
            res.push_back(i);
        }
    }
    cout << res.size() << endl;
    for (auto i : res)
    {
        cout << i << " ";
    }
    cout << endl;
}