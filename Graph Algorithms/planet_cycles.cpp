#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<int> e(n);
    vector<int> in_degree(n);
    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        x--;
        e[i] = x;
        in_degree[x]++;
    }

    vector<int> dtc(n, -1); // distance to cycle
    vector<int> cyl(n, -1); // length of the cycle the node is in or leads to
    vector<int> cyr(n, -1); // cycle representative

    // topological sort for entrances
    // perform dfs on entrances
    // remaining unseen nodes are part of cycles
    // functional graph implies we can do everything iteratively

    vector<int> q;
    for (int i = 0; i < n; i++)
    {
        if (in_degree[i] == 0)
        {
            q.push_back(i);
        }
    }

    for (int i = 0; i < q.size(); i++)
    {
        int node = q[i];
        vector<int> tail;
        while (in_degree[node] == 0)
        {
            cout << "tail node: " << node + 1 << endl;
            tail.push_back(node);
            node = e[node];
            in_degree[node]--;
        }
        for (int j = 0; j < tail.size(); j++)
        {
            cout << "tail node: " << tail[j] + 1 << endl;
            dtc[tail[j]] = tail.size() - j;
            cyr[tail[j]] = node;
            cout << "dtc[node]: " << dtc[tail[j]] << endl;
        }
    }

    for (int i = 0; i < n; i++)
    {
        if (dtc[i] != -1) // part of tail
        {
            continue;
        }
        int node = i;
        if (cyl[node] != -1) // explored cycle
        {
            continue;
        }

        vector<int> cycle = {node};
        int next_node = e[node];
        while (next_node != node)
        {
            cycle.push_back(next_node);
            next_node = e[next_node];
        }

        for (int j = 0; j < cycle.size(); j++)
        {
            cyl[cycle[j]] = cycle.size();
            dtc[cycle[j]] = 0;
            cyr[cycle[j]] = node;
        }
    }

    for (int i = 0; i < n; i++)
    {
        int distance = dtc[i];
        int cycle_rep = cyr[i];
        int cycle_len = cyl[cycle_rep];
        cout << "i, distance, cycle_len: " << i + 1 << " " << distance << " " << cycle_len << endl;
        cout << distance + cycle_len << " ";
    }
    cout << endl;
}