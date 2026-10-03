#include <bits/stdc++.h>

using namespace std;

using ll = long long;

int main()
{
    int n, m, k;
    cin >> n >> m >> k;

    // applicant desired apartment size
    vector<ll> a(n);
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    // apartment sizes
    vector<ll> b(m);
    for (int i = 0; i < m; i++)
    {
        cin >> b[i];
    }

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    int i{};
    int res{};
    for (int j = 0; j < m; j++)
    {
        while (i < n && a[i] < b[j] - k)
        {
            i++;
        }
        if (i >= n)
        {
            break;
        }

        if (b[j] - k <= a[i] && a[i] <= b[j] + k)
        {
            res++;
            i++;
        }
    }

    cout << res << endl;
}