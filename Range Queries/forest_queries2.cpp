#include <bits/stdc++.h>
using namespace std;

vector<string> grid;
vector<vector<int>> tt;
int tbase = 1;
int n;
vector<vector<int>> rst, cst;

void build_prefix_sum_arrays()
{
    while (tbase < n)
    {
        tbase *= 2;
    }
    rst.resize(tbase, vector<int>(2 * tbase));
    cst.resize(tbase, vector<int>(2 * tbase));

    // build rst
    for (int row = 0; row < n; row++)
    {
        for (int i = 0; i < n; i++)
        {
            rst[row][tbase + i] = (grid[row][i] == '*');
        }
        for (int i = tbase - 1; i > 0; i--)
        {
            rst[row][i] = rst[row][2 * i] + rst[row][2 * i + 1];
        }
    }

    // build cst
    for (int col = 0; col < n; col++)
    {
        for (int i = 0; i < n; i++)
        {
            cst[col][tbase + i] = (grid[i][col] == '*');
        }
        for (int i = tbase - 1; i > 0; i--)
        {
            cst[col][i] = cst[col][2 * i] + cst[col][2 * i + 1];
        }
    }
}

// Build the y-tree for a fixed x-node.
void build_y(int node1, int i1, int j1, int node2, int i2, int j2)
{
    if (i2 == j2)
    {
        if (i1 == j1)
        {
            tt[node1][node2] = (i1 < n && i2 < n && grid[i1][i2] == '*');
        }
        else
        {
            tt[node1][node2] = tt[2 * node1][node2] + tt[2 * node1 + 1][node2];
        }
        return;
    }

    int k2 = (i2 + j2) / 2;
    build_y(node1, i1, j1, 2 * node2, i2, k2);
    build_y(node1, i1, j1, 2 * node2 + 1, k2 + 1, j2);

    tt[node1][node2] = tt[node1][2 * node2] + tt[node1][2 * node2 + 1];
}

// Build the x-tree; for every x-node, build its full y-tree.
void helper(int node1, int i1, int j1, int node2, int i2, int j2)
{
    if (i1 != j1)
    {
        int k1 = (i1 + j1) / 2;
        helper(2 * node1, i1, k1, node2, i2, j2);
        helper(2 * node1 + 1, k1 + 1, j1, node2, i2, j2);
    }

    build_y(node1, i1, j1, node2, i2, j2);
}

// void helper(int node1, int i1, int j1, int node2, int i2, int j2)
// {
//     // cout << node1 << " " << i1 << " " << j1 << " " << node2 << " " << i2 << " " << j2 << endl;
//     if (i1 == j1)
//     {
//         // cout << "i1, node2: " << i1 << " " << node2 << endl;
//         // cout << "rst.size(), rst[0].size(): " << rst.size() << " " << rst[0].size() << endl;
//         // cout << "can we print? " << rst[i1][node2] << endl;
//         tt[node1][node2] = rst[i1][node2];
//         return;
//     }
//     if (i2 == j2)
//     {
//         tt[node1][node2] = cst[i2][node1];
//         return;
//     }
//     int k1 = (i1 + j1) / 2;
//     int k2 = (i2 + j2) / 2;
//     // can we simplify?
//     helper(node1, i1, j1, 2 * node2, i2, k2);
//     helper(node1, i1, j1, 2 * node2 + 1, k2 + 1, j2);
//     helper(2 * node1, i1, k1, node2, i2, j2);
//     helper(2 * node1, i1, k1, 2 * node2, i2, k2);
//     helper(2 * node1, i1, k1, 2 * node2 + 1, k2 + 1, j2);
//     helper(2 * node1 + 1, k1 + 1, j1, node2, i2, j2);
//     helper(2 * node1 + 1, k1 + 1, j1, 2 * node2, i2, k2);
//     helper(2 * node1 + 1, k1 + 1, j1, 2 * node2 + 1, k2 + 1, j2);

//     tt[node1][node2] = tt[node1][2 * node2] + tt[node1][2 * node2 + 1];
// }

// build 2d segment tree
void buildtt()
{
    tt.resize(2 * tbase, vector<int>(2 * tbase));
    helper(1, 0, tbase - 1, 1, 0, tbase - 1);
}

int query_helper(int node1, int i1, int j1, int node2, int i2, int j2, int e2, int f2)
{
    if (j2 < e2 || i2 > f2)
    {
        return 0;
    }
    if (e2 <= i2 && j2 <= f2)
    {
        return tt[node1][node2];
    }

    int k2 = (i2 + j2) / 2;
    return query_helper(node1, i1, j1, 2 * node2, i2, k2, e2, f2) +
           query_helper(node1, i1, j1, 2 * node2 + 1, k2 + 1, j2, e2, f2);
}

int querytt(int node1, int i1, int j1, int node2, int i2, int j2, int e1, int f1, int e2, int f2)
{
    if (j1 < e1 || i1 > f1)
    {
        return 0;
    }
    if (e1 <= i1 && j1 <= f1)
    {
        return query_helper(node1, i1, j1, node2, i2, j2, e2, f2);
    }

    int k1 = (i1 + j1) / 2;
    int q1 = querytt(2 * node1, i1, k1, node2, i2, j2, e1, f1, e2, f2);
    int q2 = querytt(2 * node1 + 1, k1 + 1, j1, node2, i2, j2, e1, f1, e2, f2);

    return q1 + q2;
}

// subdivide node2
void update_helper(int node1, int node2, int i2, int j2, int f, int delta)
{
    if (i2 == j2)
    {
        tt[node1][node2] += delta;
        return;
    }

    int k2 = (i2 + j2) / 2;
    if (f <= k2)
    {
        update_helper(node1, 2 * node2, i2, k2, f, delta);
    }
    else
    {
        update_helper(node1, 2 * node2 + 1, k2 + 1, j2, f, delta);
    }

    tt[node1][node2] = tt[node1][2 * node2] + tt[node1][2 * node2 + 1];
}

void update(int node1, int i1, int j1, int node2, int i2, int j2, int e, int f, int delta)
{
    if (i1 != j1)
    {
        int k1 = (i1 + j1) / 2;
        if (e <= k1)
        {
            update(2 * node1, i1, k1, node2, i2, j2, e, f, delta);
        }
        else
        {
            update(2 * node1 + 1, k1 + 1, j1, node2, i2, j2, e, f, delta);
        }
    }

    update_helper(node1, node2, i2, j2, f, delta);
}

int main()
{
    int q;
    cin >> n >> q;

    grid.resize(n);
    for (int i = 0; i < n; i++)
    {
        cin >> grid[i];
    }

    build_prefix_sum_arrays();
    buildtt();
    vector<int> res;
    for (int i = 0; i < q; i++)
    {
        int query_type;
        cin >> query_type;
        if (query_type == 2)
        {
            int e1, f1, e2, f2;
            cin >> e1 >> e2 >> f1 >> f2;
            e1--;
            f1--;
            e2--;
            f2--;

            res.push_back(querytt(1, 0, tbase - 1, 1, 0, tbase - 1, e1, f1, e2, f2));
        }
        else
        {
            int x, y;
            cin >> x >> y;
            x--;
            y--;

            int delta = (grid[x][y] == '*') ? -1 : 1;
            grid[x][y] = (grid[x][y] == '*') ? '.' : '*';

            update(1, 0, tbase - 1, 1, 0, tbase - 1, x, y, delta);
        }
    }

    for (auto v : res)
    {
        cout << v << endl;
    }
}