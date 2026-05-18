#include <bits/stdc++.h>
using namespace std;

struct MedianSets
{
    // invariant left.size() == ceil(k/2), right.size() == floor(k/2)
    multiset<int> left, right;
    int k;

    MedianSets(int k, vector<int> window)
    {
        this->k = k;
        for (auto x : window)
        {
            left.insert(x);
        }
        this->balance();
    }

    int median()
    {
        return *left.rbegin();
    }

    void push(int x)
    {
        if (x <= this->median())
        {
            left.insert(x);
        }
        else
        {
            right.insert(x);
        }
    }

    void pop(int x)
    {
        if (left.find(x) != left.end())
        {
            left.erase(left.find(x));
        }
        else if (right.find(x) != right.end())
        {
            right.erase(right.find(x));
        }
    }

    void balance()
    {
        if (left.size() + right.size() != k)
        {
            return;
        }

        while (left.size() > (k + 1) / 2)
        {
            int x = *left.rbegin();
            left.erase(--left.end());
            right.insert(x);
        }

        while (right.size() > k / 2)
        {
            int x = *right.begin();
            right.erase(right.begin());
            left.insert(x);
        }
    }
};

int main()
{
    int n, k;
    cin >> n >> k;

    vector<int> x(n);
    for (int i = 0; i < n; i++)
    {
        cin >> x[i];
    }

    MedianSets MS(k, vector<int>(x.begin(), x.begin() + k));
    vector<int> res = {MS.median()};
    for (int i = k; i < n; i++)
    {
        MS.push(x[i]);
        MS.pop(x[i - k]);
        MS.balance();
        res.push_back(MS.median());
    }

    for (auto v : res)
    {
        cout << v << " ";
    }
    cout << endl;
}