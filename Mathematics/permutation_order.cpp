#include <bits/stdc++.h>
using namespace std;

// least set bit determines the size of the range
// the other bits determine the index of the start of the range

vector<int> fenwick;

void update(int i, int v)
{
    while (i < fenwick.size())
    {
        fenwick[i] += v;
        i += i & -i;
    }
}

void build(int n)
{
    fenwick.resize(n + 1, 0);
    for (int i = 0; i < n; i++)
    {
        update(i + 1, 1);
    }
}

// k here being 1-indexed, i.e. k = 1 refers to the smallest
int find_kth_smallest(int k)
{
    int n = fenwick.size() - 1;
    int p = 1;
    while (2 * p <= n)
    {
        p *= 2;
    }

    int x = 0;
    // looking for the smallest index of the tree whose
    // fenwick value is >= k
    for (int i = p; i > 0; i >>= 1)
    {
        if (x + i <= n && fenwick[x + i] < k)
        {
            k -= fenwick[x + i];
            x += i;
        }
    }

    return x + 1;
}

vector<int> solve1(int n, long long k)
{
    vector<int> order;
    long long range_size = 1; // size of the current lexicographic order range
    long long range_start = 0;
    for (int i = 1; i <= n; i++)
    {
        range_size *= i;
    }

    build(n);
    while (order.size() < n)
    {
        vector<long long> buckets; // holds the start of each bucket range
        long long bucket_size = range_size / (n - order.size());
        for (int i = 0; i < (n - order.size()); i++)
        {
            buckets.push_back(range_start + bucket_size * i);
        }

        int index = upper_bound(buckets.begin(), buckets.end(), k) - buckets.begin();
        index--;

        range_start = buckets[index];
        range_size /= (n - order.size());

        // look for the index-th smallest element remaining
        int val = find_kth_smallest(index + 1);
        order.push_back(val);
        update(val, -1);
    }

    return order;
}

long long solve2(vector<int> &order)
{
    int n = order.size();
    vector<int> numbers(n);
    iota(numbers.begin(), numbers.end(), 1);

    long long range_size = 1;
    long long range_start = 0;
    for (int i = 1; i <= n; i++)
    {
        range_size *= i;
    }
    for (int i = 0; i < n; i++)
    {
        // determine which bucket k lies in
        long long bucket_size = range_size / (n - i);
        int index = lower_bound(numbers.begin(), numbers.end(), order[i]) - numbers.begin();
        numbers.erase(numbers.begin() + index);
        range_size /= (n - i);
        range_start = range_start + bucket_size * index;
    }

    return range_start;
}

int main()
{
    int t;
    cin >> t;

    while (t--)
    {
        int q;
        cin >> q;
        if (q == 1)
        {
            int n;
            long long k;
            cin >> n >> k;
            k--;

            vector<int> order = solve1(n, k);
            for (auto v : order)
            {
                cout << v << " ";
            }
            cout << '\n';
        }
        else
        {
            int n;
            cin >> n;
            vector<int> order(n);
            for (int i = 0; i < n; i++)
            {
                cin >> order[i];
            }

            cout << solve2(order) + 1 << '\n';
        }
    }
}