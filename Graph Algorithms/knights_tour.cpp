#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

vector<vector<int>> seen;

vector<pii> dir = {pii(1, -2), pii(1, 2),   pii(2, -1), pii(2, 1),
                   pii(-1, 2), pii(-1, -2), pii(-2, 1), pii(-2, -1)};

vector<pii> outgoing(int i, int j)
{
    int x = seen.size();
    int y = seen[0].size();

    vector<pii> res;
    for (auto d : dir)
    {
        int ni = i + d.first;
        int nj = j + d.second;
        if (0 <= ni && ni < x && 0 <= nj && nj < y)
        {
            if (!seen[ni][nj])
            {
                res.emplace_back(ni, nj);
            }
        }
    }

    return res;
}

vector<pii> neighbors(int i, int j)
{
    vector<pii> out = outgoing(i, j);
    sort(out.begin(), out.end(), [&](const auto &e, const auto &f)
         { return (outgoing(e.first, e.second).size() < outgoing(f.first, f.second).size()); });
    return out;
}

int dfs(pii current, int count)
{
    int i = current.first;
    int j = current.second;
    count++;
    seen[i][j] = count;
    int x = seen.size();
    int y = seen[0].size();
    if (count == x * y)
    {
        return count;
    }
    for (pii neighbor : neighbors(i, j))
    {
        int path_total = dfs(neighbor, count);
        if (path_total == x * y)
        {
            return path_total;
        }
    }
    seen[i][j] = 0;
    return 0;
}

int main()
{
    int x, y;
    cin >> x >> y;
    x--;
    y--;

    seen.resize(8, vector<int>(8));
    dfs(pii(y, x), 0);

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            cout << seen[i][j] << " ";
        }
        cout << endl;
    }
}