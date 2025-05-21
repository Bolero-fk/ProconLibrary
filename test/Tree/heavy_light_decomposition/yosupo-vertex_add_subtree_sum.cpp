// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/vertex_add_subtree_sum

#include "Tree/heavy_light_decomposition.hpp"
#include <atcoder/segtree>
#include <atcoder/modint>
#include <bits/stdc++.h>
using namespace std;

using S = long long;
S op(S a, S b)
{
    return a + b;
}

S e()
{
    return 0;
}

int main()
{
    int N, Q;
    cin >> N >> Q;

    vector<long long> a(N);
    for (int i = 0; i < N; i++)
    {
        cin >> a[i];
    }

    HeavyLightDecomposition hld(N);
    for (int i = 0; i < N - 1; i++)
    {
        int p;
        cin >> p;
        hld.add_edge(i + 1, p);
    }

    atcoder::segtree<S, op, e> seg(N);

    for (int i = 0; i < N; i++)
    {
        int pi = hld.get_pos(i);
        seg.set(pi, a[i]);
    }

    for (int q = 0; q < Q; q++)
    {
        int t;
        cin >> t;
        if (t == 0)
        {
            int u, x;
            cin >> u >> x;
            u = hld.get_pos(u);
            seg.set(u, seg.get(u) + x);
        }

        if (t == 1)
        {
            int u;
            cin >> u;

            auto [l, r] = hld.get_subtree_range(u);
            S ans = seg.prod(l, r);
            cout << ans << endl;
        }
    }

    return 0;
}