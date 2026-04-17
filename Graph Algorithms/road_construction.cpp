#include <bits/stdc++.h>
using namespace std;

vector<int> id;

int find(int i)
{
    if (id[i] == i)
    {
        return i;
    }

    id[i] = find(id[i]);
    return id[i];
}

int main()
{
    int n, m;
    cin >> n >> m;

    id.resize(n);
    for (int i = 0; i < n; i++)
    {
        id[i] = i;
    }

    vector<int> s(n, 1);
    int components = n;
    int largest_component = 0;
    for (int i = 0; i < m; i++)
    {
        int x, y;
        cin >> x >> y;
        x--;
        y--;

        int idx = find(x);
        int idy = find(y);
        int sx = s[idx];
        int sy = s[idy];

        if (idx != idy)
        {
            components--;
            largest_component = max(largest_component, sx + sy);
            if (sx < sy)
            {
                id[idx] = idy;
                s[idy] = sx + sy;
            }
            else
            {
                id[idy] = idx;
                s[idx] = sx + sy;
            }
        }
        cout << components << " " << largest_component << '\n';
    }
}