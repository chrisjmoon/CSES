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

    vector<int> tails = {-1};
    for (int i = 0; i < n; i++)
    {
        if (x[i] > tails.back())
        {
            tails.push_back(x[i]);
        }
        else
        {
            int k = lower_bound(tails.begin(), tails.end(), x[i]) - tails.begin();
            tails[k] = x[i];
        }
    }

    cout << tails.size() - 1 << endl;
}