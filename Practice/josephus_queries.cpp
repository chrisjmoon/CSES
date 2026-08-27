#include <bits/stdc++.h>

using namespace std;

int solve(int n, int k)
{
    if (n == 1)
    {
        return 1;
    }

    int remove{n / 2};
    if (k <= remove)
    {
        return 2 * k;
    }

    k -= remove;

    if (n % 2 == 0)
    {
        return 2 * solve(n / 2, k) - 1;
    }
    else
    {
        int x = solve((n + 1) / 2, k);
        if (x == 1)
        {
            return n;
        }
        return 2 * x - 3;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int q;
    cin >> q;

    while (q--)
    {
        int n, k;
        cin >> n >> k;
        cout << solve(n, k) << '\n';
    }
}