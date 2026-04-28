#include <bits/stdc++.h>
using namespace std;

using pll = pair<long long, long long>;

struct ORQueue
{
    vector<pll> in, out;

    void push(long long x)
    {
        long long agg = in.empty() ? x : (in.back().second | x);
        in.emplace_back(x, agg);
    }

    void pop()
    {
        if (out.empty())
        {
            while (in.size())
            {
                long long x = in.back().first;
                in.pop_back();
                long long agg = out.empty() ? x : (out.back().second | x);
                out.emplace_back(x, agg);
            }
        }
        out.pop_back();
    }

    long long window_or()
    {
        long long a_ = in.empty() ? 0 : in.back().second;
        long long b_ = out.empty() ? 0 : out.back().second;
        return a_ | b_;
    }
};

int main()
{
    long long n, k, x, a, b, c;
    cin >> n >> k >> x >> a >> b >> c;

    ORQueue q;

    auto next = [&]()
    {
        long long cur = x;
        x = (a * x + b) % c;
        return cur;
    };

    for (int i = 0; i < k; i++)
    {
        q.push(next());
    }

    long long ans = q.window_or();
    for (int i = k; i < n; i++)
    {
        q.pop();
        q.push(next());
        ans ^= q.window_or();
    }

    cout << ans << endl;
}