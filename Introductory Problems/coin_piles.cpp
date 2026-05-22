#include <bits/stdc++.h>
using namespace std;

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int x, y;
        cin >> x >> y;

        // determine if x = a + 2b and y = 2a + b
        // y - 2x = -3b -> (2x - y)/3 = b
        // a = (2y - x)/3

        if ((2 * x - y) % 3 != 0 || (2 * y - x) % 3 != 0 || 2 * x - y < 0 || 2 * y - x < 0)
        {
            cout << "NO" << endl;
        }
        else
        {
            cout << "YES" << endl;
        }
    }
}