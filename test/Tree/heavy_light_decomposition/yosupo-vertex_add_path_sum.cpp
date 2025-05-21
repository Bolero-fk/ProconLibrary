// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/vertex_add_path_sum

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
        int u, v;
        cin >> u >> v;
        hld.add_edge(u, v);
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
            int p, x;
            cin >> p >> x;
            p = hld.get_pos(p);
            seg.set(p, seg.get(p) + x);
        }

        if (t == 1)
        {
            int u, v;
            cin >> u >> v;

            S ans = e();
            for (auto [l, r, is_reverse] : hld.get_path_ranges(u, v))
            {
                ans = op(ans, seg.prod(l, r));
            }
            cout << ans << endl;
        }
    }

    return 0;
}