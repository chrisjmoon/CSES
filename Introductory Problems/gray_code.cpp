#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;

    if (n == 1)
    {
        cout << 0 << endl;
        cout << 1 << endl;
        return 0;
    }

    vector<string> res = {"00", "01", "11", "10"};
    for (int i = 3; i <= n; i++)
    {
        vector<string> next_res;
        for (auto v : res)
        {
            next_res.push_back("0" + v);
        }
        for (auto it = res.rbegin(); it != res.rend(); it++)
        {
            next_res.push_back("1" + *it);
        }
        swap(res, next_res);
    }

    for (auto v : res)
    {
        cout << v << endl;
    }
}