// competitive-verifier: PROBLEM https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_4_C

#include "Tree/trie.hpp"
#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n;
    cin >> n;

    Trie<char> trie;

    for (int i = 0; i < n; i++)
    {
        string S1, S2;
        cin >> S1 >> S2;
        if (S1 == "insert")
        {
            trie.insert(S2);
        }
        else
        {
            bool ans = false;
            auto find = [&](int id, bool is_end) -> void
            {
                if (is_end && 0 < trie.nodes[id].end_count)
                {
                    ans = true;
                }
            };

            trie.iterate_prefix(S2, find);
            cout << (ans ? "yes" : "no") << endl;
        }
    }

    return 0;
}