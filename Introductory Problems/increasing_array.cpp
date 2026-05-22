#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;

    vector<long long> x(n);
    long long res = 0;
    for (int i = 0; i < n; i++)
    {
        cin >> x[i];
        if (i > 0 && x[i] < x[i - 1])
        {
            res += (x[i - 1] - x[i]);
            x[i] = x[i - 1];
        }
    }

    cout << res << endl;
}