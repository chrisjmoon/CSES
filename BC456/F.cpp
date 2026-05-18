#include <bits/stdc++.h>
using namespace std;

long long MOD = 998244353;

// assuming square matrices
vector<vector<long long>> mm(const vector<vector<long long>> &a, const vector<vector<long long>> &b)
{
    int n = a.size();
    vector<vector<long long>> res(n, vector<long long>(n));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            long long t = 0;
            for (int k = 0; k < n; k++)
            {
                t = (t + (a[i][k] * b[k][j]) + MOD) % MOD;
            }
            res[i][j] = t;
        }
    }

    return res;
}

vector<vector<long long>> modpow(vector<vector<long long>> a, long long b)
{
    int n = a.size();
    vector<vector<long long>> res(n, vector<long long>(n));
    for (int i = 0; i < n; i++)
    {
        res[i][i] = 1;
    }

    if (b == 0)
    {
        return res;
    }

    while (b > 0)
    {
        if (b & 1)
        {
            res = mm(res, a);
            b -= 1;
        }

        a = mm(a, a);
        b >>= 1;
    }

    return res;
}

int main()
{
    long long n;
    int k;
    cin >> n >> k;

    vector<string> s(k);
    set<string> ss;
    for (int i = 0; i < k; i++)
    {
        cin >> s[i];
        for (int j = 1; j < s[i].size(); j++)
        {
            ss.insert(s[i].substr(0, j));
        }
    }

    ss.insert("");
    vector<string> sfv(ss.begin(), ss.end());
    int ssize = sfv.size();
    map<string, int> sid;
    for (int i = 0; i < ssize; i++)
    {
        sid[sfv[i]] = i;
    }

    // we have in our dp, states that represent prefixes of the forbidden strings
    // a letter lets us transition from a prefix to another prefix
    // if prefix + letter has a forbidden string as suffix, skip it
    // prefix + letter may have the prefix of a forbidden string as a suffix
    // can represent invalid state or empty string with empty string
    vector<vector<long long>> mt(ssize, vector<long long>(ssize));
    for (int i = 0; i < ssize; i++)
    {
        for (int j = 0; j < 26; j++)
        {
            string p = sfv[i] + (char)('a' + j);
            // check if forbidden string is a suffix of p
            bool fm = false;
            for (string fs : s)
            {
                if (fs.size() > p.size())
                {
                    continue;
                }
                if (p.substr(p.size() - fs.size(), fs.size()) == fs)
                {
                    fm = true;
                    break;
                }
            }

            if (fm)
            {
                continue;
            }

            // check the suffixes of p to find a valid dp state
            string nxt = "";
            for (int len = p.size(); len >= 1; len--)
            {
                string suf = p.substr(p.size() - len, len);
                if (ss.find(suf) != ss.end())
                {
                    nxt = suf;
                    break;
                }
            }

            mt[sid[nxt]][i] += 1;
        }
    }

    mt = modpow(mt, n);
    long long res = 0;
    for (int i = 0; i < ssize; i++)
    {
        res = (res + mt[i][sid[""]] + MOD) % MOD;
    }

    cout << res << endl;
}