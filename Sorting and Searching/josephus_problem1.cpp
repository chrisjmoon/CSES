// #include <bits/stdc++.h>
// using namespace std;

// #define FAST_IO                       \
//     ios_base::sync_with_stdio(false); \
//     cin.tie(NULL);

// // int: 32 bits -+ 2**9
// // long: 32 or 64 bits depending on the platform
// // long long: 64 bits -+ 9**18
// #define ll long long
// #define vi vector<int>
// #define vii vector<pair<int, int>>
// #define pii pair<int, int>
// #define rep(i, a, b) for (int i = a; i < b; ++i)
// #define all(v) v.begin(), v.end()
// #define pb push_back
// #define endl "\n"

// // // Constants
// // const int MOD = 1e9 + 7;
// // const int INF = 1e9;

// // // Utility functions
// // ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }
// // ll lcm(ll a, ll b) { return (a / gcd(a, b)) * b; }

// // // print vector
// // template <typename T>
// // void print_vector(const std::vector<T> &vec)
// // {
// //     for (const T &x : vec)
// //     {
// //         std::cout << x << " ";
// //     }
// //     std::cout << '\n';
// // }

// // // binary exponentiation
// // ll pow(ll x, ll y, ll MOD = 0)
// // {
// //     ll res = 1;
// //     while (y > 0)
// //     {
// //         if (y % 2)
// //         {
// //             res *= x;
// //             if (MOD != 0)
// //                 res %= MOD;
// //             y -= 1;
// //         }
// //         else
// //         {
// //             x *= x;
// //             if (MOD != 0)
// //                 x %= MOD;
// //             y /= 2;
// //         }
// //     }

// //     return res;
// // }

// // int main()
// // {
// //     ios::sync_with_stdio(false);
// //     cin.tie(nullptr);

// //     int n;
// //     cin >> n;

// //     vector<int> a;
// //     // 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
// //     // 2 4 6 8 10 12 14 16 18 20
// //     // 3 7 11 15 ...
// //     // can we merge with even logic?
// //     // find first, increment
// //     int d = 2;
// //     int i = 2;
// //     bool sf = false;
// //     vector<int> s(n + 1, false);
// //     while (a.size() < n)
// //     {
// //         while (i <= n)
// //         {
// //             a.push_back(i);
// //             s[i] = true;
// //             i += d;
// //         }
// //         if (i - d / 2 <= n && !s[i - d / 2])
// //         {
// //             sf = false;
// //         }
// //         else
// //         {
// //             sf = true;
// //         }
// //         for (int j = 1; j <= n; j++)
// //         {
// //             if (!s[j])
// //             {
// //                 if (sf)
// //                 {
// //                     sf = false;
// //                 }
// //                 else
// //                 {
// //                     i = j;
// //                     break;
// //                 }
// //             }
// //         }
// //         d *= 2;
// //     }

// //     for (int i = 0; i < n; i++)
// //     {
// //         cout << a[i] << " ";
// //     }
// //     cout << endl;
// // }

// int josephus(int n)
// {
//     if (n == 1)
//         return 1;
//     return (josephus(n - 1) + 2 - 1) % n + 1;
// }

// int main()
// {
//     int n;
//     cin >> n;

//     vector<int> res;
//     int l = 1 << (31 - __builtin_clz(n)); // largest power of 2 ≤ n
//     for (int i = 1; i <= n; ++i)
//     {
//         int l = 1 << (31 - __builtin_clz(i)); // Most significant bit
//         res.push_back(2 * (i - l) + 1);
//     }

//     for (int x : res)
//         cout << x << " ";
//     cout << "\n";
// }
#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    queue<int> q;
    for (int i = 1; i <= n; i++)
    {
        q.push(i);
    }

    vector<int> a;
    a.reserve(n);

    bool rn = true;
    while (!q.empty())
    {
        int x = q.front();
        q.pop();

        if (rn)
        {
            q.push(x);
        }
        else
        {
            a.push_back(x);
        }
        rn = !rn;
    }

    for (int i = 0; i < n; i++)
    {
        cout << a[i] << " ";
    }
    cout << endl;
}
