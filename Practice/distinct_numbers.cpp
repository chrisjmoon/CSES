#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    // erase and unique -> take the new size
    // what unique does is eliminate identical adjacent values

    sort(a.begin(), a.end());
    a.erase(unique(a.begin(), a.end()), a.end());

    cout << a.size() << endl;
}