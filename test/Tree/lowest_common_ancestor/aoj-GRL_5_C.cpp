// competitive-verifier: PROBLEM https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_C&lang=ja

#include "Tree/lowest_common_ancestor.hpp"
#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n;
    cin >> n;
    LCA lca(n);

    for (int i = 0; i < n; i++)
    {
        int k;
        cin >> k;
        for (int j = 0; j < k; j++)
        {
            int c;
            cin >> c;
            lca.add_edge(i, c), lca.add_edge(c, i);
        }
    }

    int q;
    cin >> q;
    for (int i = 0; i < q; i++)
    {
        int u, v;
        cin >> u >> v;
        cout << lca.find(u, v) << endl;
    }

    return 0;
}