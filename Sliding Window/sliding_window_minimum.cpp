#include <bits/stdc++.h>
using namespace std;

using pll = pair<long long, int>;

int main()
{
    long long n, k, x, a, b, c;
    cin >> n >> k >> x >> a >> b >> c;

    // suppose 2 is the minimum
    // window slides over to 4
    // then slides over to 3; we can pop 4

    vector<long long> window;
    deque<pll> q;
    for (int i = 0; i < k; i++)
    {
        window.push_back(x);
        while (q.size() && q.back().first > x)
        {
            q.pop_back();
        }
        q.emplace_back(x, i);
        x = (a * x + b) % c;
    }

    long long res = 0;
    for (int i = 0; i < n - k + 1; i++)
    {
        res ^= q.front().first;
        // move forward
        if (q.front().second < i + 1)
        {
            q.pop_front();
        }
        while (q.size() && q.back().first > x)
        {
            q.pop_back();
        }
        q.emplace_back(x, i + k);
        x = (a * x + b) % c;
    }

    cout << res << endl;
}