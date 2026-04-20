#include <bits/stdc++.h>
using namespace std;

int solve(int n, int k, bool offset)
{
    // normally we would begin on 1
    // but if offset is true, we begin on 0
    if (n == 1)
    {
        return 0;
    }

    int val = 2 * k - 1 - offset;
    if (val > (n - 1))
    {
        if (offset)
        {
            int res = solve(n / 2, k - ((n + 1) / 2), !(((n % 2) == 0) ^ offset));
            return 2 * res + 1;
        }
        else
        {
            int res = solve((n + 1) / 2, k - (n / 2), !(((n % 2) == 0) ^ offset));
            return 2 * res;
        }
    }
    else
    {
        return val;
    }
}

long long kth(int n, int k)
{
    long long remove = n / 2; // amount we are removing
    if (k <= remove)
    {
        return 2 * k;
    }
    k -= remove;
    if (n % 2 == 0)
    {
        return 2 * kth(n / 2, k) - 1;
    }
    else
    {
        if (k == 1)
        {
            return 1;
        }
        // 1 3 5 7 9
        // 1 2 3 4 5
        // 1 -> 1
        // want 2 -> 1, 4 -> 5
        return 2 * kth(n / 2, k - 1) + 1;
    }
}

int main()
{
    int q;
    cin >> q;

    for (int i = 0; i < q; i++)
    {
        int n, k;
        cin >> n >> k;
        cout << kth(n, k) << endl;
    }
}