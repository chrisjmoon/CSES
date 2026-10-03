#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n;
    cin >> n;

    // define the relation as A -> B if B is the boss of A
    // determine in degree
    int in[n]{};
    int bo[n]{};

    bo[0] = -1; // general director has no boss

    for (int i = 0; i < n - 1; i++)
    {
        int boss;
        cin >> boss;
        boss--;

        // the boss of worker i + 1 is boss
        in[boss]++;
        bo[i + 1] = boss;
    }

    int subordinates[n]{};

    queue<int> q;
    for (int i = 0; i < n; i++)
    {
        if (in[i] == 0)
        {
            q.push(i);
        }
    }

    while (q.size())
    {
        int worker = q.front();
        q.pop();

        if (bo[worker] != -1)
        {
            int boss = bo[worker];
            in[boss]--;

            subordinates[boss] += subordinates[worker] + 1;

            if (in[boss] == 0)
            {
                q.push(boss);
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        cout << subordinates[i] << " ";
    }
    cout << endl;
}