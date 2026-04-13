#include <bits/stdc++.h>
using namespace std;

long long MOD = 1e9 + 7;

// size of {0 <= y <= x | y satisfies criteria}
long long helper(long long x)
{
    // [0 - 10)
    // [10 - 100)
    // [100 - 1000)

    // find all d digit numbers that fit criteria <= x
    int d = 0;
    vector<int> x_;
    for (int i = x; i > 0; i /= 10)
    {
        d++;
        x_.push_back(i % 10);
    }
    reverse(x_.begin(), x_.end());

    long long res = 0;
    for (int i = d - 1; i >= 0; i--)
    {
        int start = i > 0 ? 0 : 1;
        for (int j = start; j < x_[i]; j++)
        {
            if (j == x_[i - 1])
            {
                continue;
            }
            res = (res + (long long)pow(9, d - 1 - i)) % MOD;
        }
    }
}

int main()
{
    //
}