#include <bits/stdc++.h>
using namespace std;

long MOD = 1e9 + 7;

struct trie
{
    bool boundary{false}; // whether the node represents a prefix boundary
    array<trie *, 26> next_node{};
};

int main()
{
    string s;
    cin >> s;

    int n = s.size();

    int k;
    cin >> k;

    vector<string> words(k);
    for (int i = 0; i < k; i++)
    {
        cin >> words[i];
    }

    trie head_node;
    head_node.boundary = true;
    trie *current_node;
    for (auto word : words)
    {
        current_node = &head_node;
        for (auto ch : word)
        {
            if (current_node->next_node[ch - 'a'] == nullptr)
            {
                current_node->next_node[ch - 'a'] = new trie();
            }

            current_node = current_node->next_node[ch - 'a'];
        }

        current_node->boundary = true;
    }

    vector<long> count(n + 1);
    count[0] = 1;
    for (int i = 0; i < n; i++)
    {
        if (count[i] == 0)
        {
            continue;
        }

        int j{i};
        current_node = &head_node;
        while (j < n)
        {
            current_node = current_node->next_node[s[j] - 'a'];
            if (current_node == nullptr)
            {
                break;
            }

            j++;
            if (current_node->boundary)
            {
                count[j] = (count[j] + count[i]) % MOD;
            }
        }
    }

    cout << count[n] << endl;
}