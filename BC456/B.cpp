#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;

    vector<vector<int>> grid(n, vector<int>(m));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            int k = 0;
            k += (i > 0);
            k += (i < n - 1);
            k += (j > 0);
            k += (j < m - 1);
            cout << k << " ";
        }
        cout << endl;
    }
}