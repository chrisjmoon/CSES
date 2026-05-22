#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;

    if (n == 1)
    {
        cout << 1 << endl;
        return 0;
    }
    if (n <= 3)
    {
        cout << "NO SOLUTION" << endl;
        return 0;
    }

    deque<int> p = {2, 4, 1, 3};
    for (int i = 5; i <= n; i++)
    {
        if (i % 2 == 0)
        {
            p.push_front(i);
        }
        else
        {
            p.push_back(i);
        }
    }

    for (auto v : p)
    {
        cout << v << " ";
    }
    cout << endl;
}