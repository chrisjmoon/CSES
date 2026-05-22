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

        long long layer = max(x, y);
        long long base = layer * layer;
        if (layer % 2 == 1)
        {
            if (y == layer)
            {
                cout << base - x + 1 << endl;
            }
            else
            {
                cout << (layer - 1) * (layer - 1) + y << endl;
            }
        }
        else
        {
            if (y == layer)
            {
                cout << (layer - 1) * (layer - 1) + x << endl;
            }
            else
            {
                cout << base - y + 1 << endl;
            }
        }
    }
}