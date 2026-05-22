#include <bits/stdc++.h>
using namespace std;

int main()
{
    long long n;

    cin >> n;
    // count the number of 5's
    int res = 0;
    long long f = 5;
    while (f <= n)
    {
        res += (n / f);
        f *= 5;
    }

    cout << res << endl;
}