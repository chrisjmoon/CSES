#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, k;
    cin >> n >> k;

    // xor of all window sums
    // x_1 = x
    // x_i = a * x_{i - 1} + b (mod c)

    long long x, a, b, c;
    cin >> x >> a >> b >> c;

    long long res = 0;
    long long window = 0;
    long long start = x;
    long long end = x;
    for (int i = 0; i < k; i++)
    {
        window += end;
        end = (a * end + b) % c;
    }

    for (int i = 0; i < n - k + 1; i++)
    {
        res ^= window;
        window -= start;
        start = (a * start + b) % c;
        window += end;
        end = (a * end + b) % c;
    }

    cout << res << endl;
}