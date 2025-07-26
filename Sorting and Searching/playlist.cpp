#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <cmath>
#include <queue>
#include <stack>
#include <bitset>
using namespace std;

// Macros for easier access
#define ll long long
#define ull unsigned long long
#define pii pair<int, int>
#define pll pair<ll, ll>
#define vi vector<int>
#define vll vector<ll>
#define vpii vector<pii>
#define vpll vector<pll>
#define pb push_back
#define mp make_pair
#define all(x) (x).begin(), (x).end()
#define fi first
#define se second
#define sz(x) (int)(x).size()

// Fast I/O
#define fastio                      \
  ios_base::sync_with_stdio(false); \
  cin.tie(NULL);                    \
  cout.tie(NULL);

// Debugging
#define debug(x) cerr << #x << " = " << x << '\n'
#define debugv(v)      \
  cerr << #v << " = "; \
  for (auto x : v)     \
    cerr << x << ' ';  \
  cerr << '\n'

// Constants
const int INF = 1e9;
const ll LINF = 1e18;
const int MOD = 1e9 + 7;

// Function to solve the problem
void solve()
{
  // Your code here
}

int main()
{
  fastio;

  // int n;
  // cin >> n;
  // vector<long> p(n);
  // map<long, int> m;
  // int res = 0;
  // int ll_ = -1; // max index of seen left bounds
  // for (int i = 0; i < n; i++)
  // {
  //   cin >> p[i];
  //   if (m.count(p[i]))
  //   {
  //     if (ll_ < m[p[i]])
  //     {
  //       res = max(res, i - ll_ - 1);
  //     }
  //     else
  //     {
  //       res = max(res, i - ll_);
  //     }
  //     ll_ = max(m[p[i]], ll_);
  //   }
  //   else
  //   {
  //     res = max(res, i - ll_);
  //   }
  //   m[p[i]] = i;
  // }
  // cout << res << endl;

  int n;
  cin >> n;
  vector<long> p(n);
  for (int i = 0; i < n; i++)
  {
    cin >> p[i];
  }

  // coordinate compress
  vector<long> v = p;
  sort(v.begin(), v.end());
  v.erase(unique(v.begin(), v.end()), v.end());
  int m = v.size();
  vector<int> last_pos(m, -1);

  int res = 0;
  int l = -1;
  for (int i = 0; i < n; i++)
  {
    int id = lower_bound(v.begin(), v.end(), p[i]) - v.begin();
    l = max(l, last_pos[id] + 1);
    res = max(res, i - l + 1);
    last_pos[id] = i;
  }

  cout << res << endl;
  return 0;
}