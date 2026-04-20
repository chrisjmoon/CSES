#include <bits/stdc++.h>
using namespace std;

bool prime(long long x)
{
    if (x < 2)
    {
        return false;
    }
    if (x % 2 == 0)
    {
        return x == 2;
    }
    for (long long i = 3; i * i <= x; i += 2)
    {
        if (x % i == 0)
        {
            return false;
        }
    }
    return true;
}

long long solve(long long x)
{
    while (true) // by PNT, this should stop in log(x)
    {
        x++;
        if (prime(x))
        {
            return x;
        }
    }
}

int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        long long x;
        cin >> x;

        cout << solve(x) << endl;
    }
}