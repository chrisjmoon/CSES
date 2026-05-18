#include <bits/stdc++.h>
using namespace std;

int main()
{
    string s;
    cin >> s;
    int n = s.size();

    long long res = 0;
    for (int i = 0; i < n; i++)
    {
        if (s[i] == 'C')
        {
            res += min(n - 1 - i, i) + 1;
        }
    }

    cout << res << endl;
}