#include <bits/stdc++.h>
using namespace std;

int main()
{
    long long n;
    cin >> n;

    if (n * (n + 1) % 4 != 0)
    {
        cout << "NO" << endl;
        return 0;
    }

    cout << "YES" << endl;
    long long target = n * (n + 1) / 4;
    vector<bool> p(n + 1);
    int count = 0;
    for (int i = n; i >= 1; i--)
    {
        if (target >= i)
        {
            p[i] = true;
            count++;
            target -= i;
        }
    }

    cout << count << endl;
    for (int i = 0; i < n; i++)
    {
        if (p[i + 1])
        {
            cout << i + 1 << " ";
        }
    }
    cout << endl;
    cout << (n - count) << endl;
    for (int i = 0; i < n; i++)
    {
        if (!p[i + 1])
        {
            cout << i + 1 << " ";
        }
    }
}