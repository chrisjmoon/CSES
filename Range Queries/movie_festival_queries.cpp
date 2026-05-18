#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, q;
    cin >> n >> q;

    vector<pair<int, int>> movies;
    vector<int> cc;
    for (int i = 0; i < n; i++)
    {
        int a, b;
        cin >> a >> b;
        movies.emplace_back(a, b);
        cc.push_back(a);
        cc.push_back(b);
    }

    vector<pair<int, int>> queries;
    for (int i = 0; i < q; i++)
    {
        int a, b;
        cin >> a >> b;
        queries.emplace_back(a, b);
        cc.push_back(a);
        cc.push_back(b);
    }

    // compress
    sort(cc.begin(), cc.end());
    cc.erase(unique(cc.begin(), cc.end()), cc.end());
    int m = cc.size();
    for (int i = 0; i < n; i++)
    {
        int a = lower_bound(cc.begin(), cc.end(), movies[i].first) - cc.begin();
        int b = lower_bound(cc.begin(), cc.end(), movies[i].second) - cc.begin();
        movies[i] = {a, b};
    }
    for (int i = 0; i < q; i++)
    {
        int a = lower_bound(cc.begin(), cc.end(), queries[i].first) - cc.begin();
        int b = lower_bound(cc.begin(), cc.end(), queries[i].second) - cc.begin();
        queries[i] = {a, b};
    }

    // sort by start times
    sort(movies.begin(), movies.end(),
         [&](const auto &a, const auto &b) { return a.first < b.first; });
    vector<int> sm(m); // suffix minimum for end times; sm[i] = minimum end time among movies that
                       // start on or after i
    int j = n - 1;
    int min_end = m;
    for (int i = m - 1; i >= 0; i--)
    {
        while (j >= 0 && movies[j].first >= i)
        {
            min_end = min(min_end, movies[j].second);
            j--;
        }
        sm[i] = min_end;
    }

    // bl[0][i]: the earliest you can end starting a movie on or after time i
    // bl[1][i]: the earliest you can end after watching two movies that begin on or after time i
    int EXP = 20;
    vector<vector<int>> bl(EXP, vector<int>(m, -1));
    for (int i = 0; i < m; i++)
    {
        bl[0][i] = sm[i];
    }
    bl[0][m] = m;

    for (int i = 1; i < EXP; i++)
    {
        for (int j = 0; j < m; j++)
        {
            bl[i][j] = bl[i - 1][bl[i - 1][j]];
        }
        bl[i][m] = m;
    }

    vector<int> res;
    for (int i = 0; i < q; i++)
    {
        int a = queries[i].first;
        int b = queries[i].second;

        int left_end = a;
        int jumps = 0;
        for (int e = EXP - 1; e >= 0; e--)
        {
            if (bl[e][left_end] <= b)
            {
                jumps += (1 << e);
                left_end = bl[e][left_end];
            }
        }
        res.push_back(jumps);
    }

    for (auto v : res)
    {
        cout << v << endl;
    }
}