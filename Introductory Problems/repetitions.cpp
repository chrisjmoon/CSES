#include <bits/stdc++.h>
using namespace std;

int main()
{
    string s;
    cin >> s;

    char c = 'Z';
    int res = 0;
    int cc = 0;
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == c)
        {
            cc++;
        }
        else
        {
            res = max(res, cc);
            c = s[i];
            cc = 1;
        }
    }

    res = max(res, cc);

    cout << res << endl;
}