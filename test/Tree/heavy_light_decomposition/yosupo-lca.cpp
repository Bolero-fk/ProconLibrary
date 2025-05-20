// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/lca

#include "Tree/heavy_light_decomposition.hpp"
#include <atcoder/segtree>
#include <bits/stdc++.h>
using namespace std;

int main()
{
    int N, Q;
    cin >> N >> Q;

    HeavyLightDecomposition hld(N);

    for (int i = 0; i < N - 1; i++)
    {
        int p;
        cin >> p;
        hld.add_edge(i + 1, p);
    }

    for (int i = 0; i < Q; i++)
    {
        int u, v;
        cin >> u >> v;
        cout << hld.lca(u, v) << endl;
    }

    return 0;
}