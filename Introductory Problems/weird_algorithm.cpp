#include <bits/stdc++.h>

using namespace std;

int main()
{
    long long n;
    cin >> n;

    vector<long long> res;
    while (n != 1)
    {
        res.push_back(n);
        if (n % 2 == 0)
        {
            n /= 2;
        }
        else
        {
            n *= 3;
            n += 1;
        }
    }

    res.push_back(1);
    for (auto v : res)
    {
        cout << v << " ";
    }
    cout << endl;
}