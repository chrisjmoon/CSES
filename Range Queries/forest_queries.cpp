#include <bits/stdc++.h>
using namespace std;

vector<string> grid;

int main()
{
    int n, q;
    cin >> n >> q;

    grid.resize(n);
    vector<vector<int>> prefix(n + 1, vector<int>(n + 1));
    for (int i = 0; i < n; i++)
    {
        cin >> grid[i];
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int t = (grid[i][j] == '*' ? 1 : 0);
            prefix[i + 1][j + 1] = prefix[i][j + 1] + prefix[i + 1][j] - prefix[i][j] + t;
        }
    }

    vector<int> res;
    while (q--)
    {
        int i, j, i_, j_;
        cin >> i >> j >> i_ >> j_;

        i--;
        j--;
        i_--;
        j_--;

        res.push_back(prefix[i_ + 1][j_ + 1] - prefix[i][j_ + 1] - prefix[i_ + 1][j] +
                      prefix[i][j]);
    }

    for (auto v : res)
    {
        cout << v << endl;
    }
}