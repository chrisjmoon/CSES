#include <bits/stdc++.h>
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

  int n;
  cin >> n;

  set<int> s;
  int res = 0;
  for (int i = 0; i < n; i++) {
    int x;
    cin >> x;
    if (s.count(x + 1)) {
      res += 1;
    }
    s.insert(x);
  }

  cout << res + 1 << endl;

  return 0;
}