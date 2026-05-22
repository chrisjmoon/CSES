#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;

    vector<int> seen(n + 1);
    for (int i = 0; i < n - 1; i++)
    {
        int a;
        cin >> a;
        seen[a] = true;
    }

    for (int i = 0; i < n; i++)
    {
        if (!seen[i + 1])
        {
            cout << i + 1 << endl;
            return 0;
        }
    }
}