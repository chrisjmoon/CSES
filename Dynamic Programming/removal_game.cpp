#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<long long> x(n);
    long long sum = 0;
    for (int i = 0; i < n; i++)
    {
        cin >> x[i];
        sum += x[i];
    }

    // stores the max difference between the score of the current and other player
    vector<vector<long long>> a(n, vector<long long>(n));
    for (int i = 0; i < n; i++)
    {
        a[i][i] = x[i];
    }

    for (int i = 2; i <= n; i++)
    {
        for (int j = 0; j + i - 1 < n; j++)
        {
            a[j][j + i - 1] = max(x[j] - a[j + 1][j + i - 1], x[j + i - 1] - a[j][j + i - 2]);
        }
    }

    cout << (sum + a[0][n - 1]) / 2 << endl;
}