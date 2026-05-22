#include <bits/stdc++.h>
using namespace std;

int main()
{
    string s;
    cin >> s;

    vector<int> c(26);
    for (int i = 0; i < s.size(); i++)
    {
        c[s[i] - 'A']++;
    }

    char middle;
    int oc = 0;
    for (int i = 0; i < 26; i++)
    {
        if (c[i] % 2)
        {
            middle = (char)(i + 'A');
            oc++;
        }
    }

    if (oc > 1)
    {
        cout << "NO SOLUTION" << endl;
        return 0;
    }

    string res;
    for (int i = 0; i < 26; i++)
    {
        for (int j = 0; j < c[i] / 2; j++)
        {
            res.push_back((char)(i + 'A'));
        }
    }

    string res_ = res;
    reverse(res.begin(), res.end());
    if (oc == 1)
    {
        res += middle;
    }
    res += res_;

    cout << res << endl;
}