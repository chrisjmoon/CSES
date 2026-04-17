#include <bits/stdc++.h>
using namespace std;

void walk(int current, vector<bool> &eu, int incoming_bit, vector<int> &history, int n)
{
    for (int i = 0; i < 2; i++)
    {
        int edge;
        if (i == 0)
        {
            edge = current;
        }
        else
        {
            edge = current + (1 << n - 1);
        }
        if (!eu[edge])
        {
            eu[edge] = true;
            int next_bit = i;
            int neighbor = edge / 2;
            walk(neighbor, eu, next_bit, history, n);
        }
    }

    if (incoming_bit != -1)
    {
        history.push_back(incoming_bit);
    }
}

int main()
{
    int n;
    cin >> n;

    vector<bool> eu(1 << n);

    // eulerian circuit
    vector<int> history;
    walk(0, eu, -1, history, n);
    reverse(history.begin(), history.end());
    for (int i = 0; i < n - 1; i++)
    {
        cout << 0;
    }
    for (auto v : history)
    {
        cout << v;
    }
    cout << endl;
}