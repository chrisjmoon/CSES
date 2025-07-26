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

  int n, m;
  cin >> n >> m;
  vector<int> x(n);
  vector<int> v(n + 1);
  int res = 1;
  for (int i = 0; i < n; i++)
  {
    cin >> x[i];
    v[x[i]] = i;
    if (v[x[i] + 1] != -1)
    {
      res++;
    }
  }

  for (int i = 0; i < m; i++)
  {
    int a, b;
    cin >> a >> b;
    a--;
    b--;

    vector<int> tmp = {x[a], x[b]};
    vector<int> sn = {-1, 1};

    for (int j = 0; j < 2; j++)
    {
      for (int k = 0; k < 2; k++)
      {
        if (a <= v[tmp[j] + sn[k]] && v[tmp[j] + sn[k]] <= b)
        {
          if (j == 0)
          {
            res += sn[k];
          }
          else
          {
            res -= sn[k];
          }
        }
      }
    }

    if (x[a] == x[b] + 1)
    {
      res += 1;
    }
    if (x[b] == x[a] + 1)
    {
      res -= 1;
    }

    // swap values at indices a, b
    swap(v[x[a]], v[x[b]]);
    swap(x[a], x[b]);

    cout << res << endl;
  }

  return 0;
}