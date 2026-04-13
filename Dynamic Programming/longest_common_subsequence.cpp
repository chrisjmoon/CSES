#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;

    vector<int> a(n), b(m);
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    for (int i = 0; i < m; i++)
    {
        cin >> b[i];
    }

    vector<vector<int>> prev(m + 1, vector<int>(0)), cur(m + 1, vector<int>(0));
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (a[i - 1] == b[j - 1])
            {
                cur[j] = prev[j - 1];
                cur[j].push_back(b[j - 1]);
            }
            else
            {
                if (prev[j].size() > cur[j - 1].size())
                {
                    cur[j] = prev[j];
                }
                else
                {
                    cur[j] = cur[j - 1];
                }
            }
        }
        prev = cur;
        cur = vector<vector<int>>(m + 1, vector<int>(0));
    }

    cout << prev[m].size() << endl;
    for (int i = 0; i < prev[m].size(); i++)
    {
        cout << prev[m][i] << " ";
    }
    cout << endl;
}