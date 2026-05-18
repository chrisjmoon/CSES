#include <bits/stdc++.h>
using namespace std;

int main()
{
    string s;
    int n;
    cin >> s >> n;

    int m = s.size();
    cout << s.substr(n, m - 2 * n) << endl;
}