// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/lca
// competitive-verifier: TLE 5

#include "Tree/lowest_common_ancestor.hpp"
#include <bits/stdc++.h>

using namespace std;

int main()
{
    int N, Q;
    cin >> N >> Q;
    LCA lca(N);

    for (int i = 0; i < N - 1; i++)
    {
        int p;
        cin >> p;
        lca.add_edge(p, i + 1);
    }
    for (int i = 0; i < Q; i++)
    {
        int u, v;
        cin >> u >> v;
        cout << lca.find(u, v) << endl;
    }

    return 0;
}