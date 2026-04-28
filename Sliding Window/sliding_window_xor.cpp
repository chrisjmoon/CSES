#include <bits/stdc++.h>
using namespace std;

int main()
{
    long long n, k, x, a, b, c;
    cin >> n >> k >> x >> a >> b >> c;

    long long res = 0;
    for (int i = 0; i < n; i++)
    {
        // x contributes at most once to the res
        // [i - k + 1, i] ... [i, i + k - 1]
        // k windows

        int min_index = max(int(i - k + 1), 0);
        int max_index = min(i + k - 1, n - 1) - (k - 1);
        if ((max_index - min_index + 1) % 2)
        {
            // cout << "x: " << x << endl;
            // cout << "min_index, max_index: " << min_index << " " << max_index << endl;
            res ^= x;
        }

        x = (a * x + b) % c;
    }

    cout << res << endl;
}