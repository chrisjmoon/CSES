#include <bits/stdc++.h>
using namespace std;

struct MedianMultisets
{
    multiset<int> left, right;
    int k;
    deque<int> window;
    long long left_sum, right_sum;

    MedianMultisets(int k, vector<int> window) : k(k), window(window.begin(), window.end())
    {
        this->left_sum = 0;
        this->right_sum = 0;
        for (auto x : window)
        {
            this->left.insert(x);
            left_sum += x;
        }
        this->balance();
    }

    long long get_res()
    {
        // get median and return sum of the absolute difference with median
        int median = this->get_median();

        return (median * left.size() - left_sum) + (right_sum - median * right.size());
    }

    int get_median()
    {
        return *left.rbegin();
    }

    void push(int x)
    {
        window.push_back(x);
        if (x <= this->get_median())
        {
            left.insert(x);
            left_sum += x;
        }
        else
        {
            right.insert(x);
            right_sum += x;
        }
        this->balance();
    }

    void pop()
    {
        int x = window.front();
        window.pop_front();
        if (left.find(x) != left.end())
        {
            left.erase(left.find(x));
            left_sum -= x;
        }
        else if (right.find(x) != right.end())
        {
            right.erase(right.find(x));
            right_sum -= x;
        }
        this->balance();
    }

    void balance()
    {
        int l = left.size() + right.size();
        while (left.size() > (l + 1) / 2)
        {
            int x = *left.rbegin();
            left.erase(--left.end());
            right.insert(x);
            left_sum -= x;
            right_sum += x;
        }
        while (right.size() > l / 2)
        {
            int x = *right.begin();
            right.erase(right.begin());
            left.insert(x);
            right_sum -= x;
            left_sum += x;
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

    MedianMultisets MS(k, vector<int>(x.begin(), x.begin() + k));
    vector<long long> res = {MS.get_res()};
    for (int i = k; i < n; i++)
    {
        MS.push(x[i]);
        MS.pop();
        res.push_back(MS.get_res());
    }

    for (auto v : res)
    {
        cout << v << " ";
    }
    cout << endl;
}