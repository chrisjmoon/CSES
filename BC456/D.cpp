#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int x, q;
    cin >> x;
    cin >> q;

    multiset<int> l, r;
    l.insert(x);

    while (q--)
    {
        int a, b;
        cin >> a >> b;
        if (a <= *l.rbegin())
        {
            l.insert(a);
        }
        else
        {
            r.insert(a);
        }

        if (b <= *l.rbegin())
        {
            l.insert(b);
        }
        else
        {
            r.insert(b);
        }

        int t = l.size() + r.size();
        while (l.size() > (t + 1) / 2)
        {
            int left_largest = *l.rbegin();
            l.erase(prev(l.end()));
            r.insert(left_largest);
        }
        while (r.size() > t / 2)
        {
            int right_smallest = *r.begin();
            r.erase(r.begin());
            l.insert(right_smallest);
        }

        cout << *l.rbegin() << '\n';
    }
}