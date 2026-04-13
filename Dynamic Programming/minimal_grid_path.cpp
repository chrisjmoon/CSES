#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<string> g(n);
    for (int i = 0; i < n; i++)
    {
        cin >> g[i];
    }

    vector<vector<bool>> d(n, vector<bool>(n, false));
    d[0][0] = true;
    string res = "";
    for (int i = 0; i < 2 * n - 1; i++)
    {
        char mc = 'Z';
        vector<pair<int, int>> diagonal;
        int x, y;
        if (i < n)
        {
            x = i;
            y = 0;
        }
        else
        {
            x = n - 1;
            y = i - n + 1;
        }
        while (y < n && x >= 0)
        {
            if (d[x][y])
            {
                diagonal.emplace_back(x, y);
            }
            x--;
            y++;
        }

        for (auto p : diagonal)
        {
            if (g[p.first][p.second] < mc)
            {
                mc = g[p.first][p.second];
            }
        }
        for (auto p : diagonal)
        {
            if (g[p.first][p.second] == mc)
            {
                if (p.first + 1 < n)
                {
                    d[p.first + 1][p.second] = true;
                }
                if (p.second + 1 < n)
                {
                    d[p.first][p.second + 1] = true;
                }
            }
        }

        res += mc;
    }

    cout << res << endl;
}