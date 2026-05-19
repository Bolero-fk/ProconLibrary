// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/aho_corasick

#include "Tree/aho_corasick.hpp"
#include <bits/stdc++.h>
using namespace std;

int main()
{
    int N;
    cin >> N;

    AhoCorasick<char> aho_cora;
    vector<string> S(N);
    vector<int> terminal_node_ids(N);
    for (int i = 0; i < N; i++)
    {
        cin >> S[i];
        terminal_node_ids[i] = aho_cora.insert(S[i]);
    }

    aho_cora.build();

    cout << aho_cora.size() << endl;
    for (int i = 1; i < aho_cora.size(); i++)
    {
        cout << aho_cora.parent(i) << " " << aho_cora.get_suffix_link(i) << endl;
    }

    for (int i = 0; i < N; i++)
    {
        cout << terminal_node_ids[i] << " ";
    }
    cout << endl;

    return 0;
}