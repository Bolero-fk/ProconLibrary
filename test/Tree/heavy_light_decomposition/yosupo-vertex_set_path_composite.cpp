// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/vertex_set_path_composite

#include "Tree/heavy_light_decomposition.hpp"
#include <atcoder/segtree>
#include <atcoder/modint>
#include <bits/stdc++.h>
using namespace std;

struct S
{
    atcoder::modint998244353 f(int x)
    {
        return a * x + b;
    }

    atcoder::modint998244353 a, b;
};

S op_l_to_r(S a, S b)
{
    return S(a.a * b.a, a.b * b.a + b.b);
}

S op_r_to_l(S a, S b)
{
    return S(b.a * a.a, b.b * a.a + a.b);
}

S e()
{
    return S(1, 0);
}

int main()
{
    int N, Q;
    cin >> N >> Q;

    vector<array<int, 2>> ab(N);
    for (int i = 0; i < N; i++)
    {
        cin >> ab[i][0] >> ab[i][1];
    }

    HeavyLightDecomposition hld(N);
    for (int i = 0; i < N - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        hld.add_edge(u, v);
    }

    atcoder::segtree<S, op_l_to_r, e> seg_l(N);
    atcoder::segtree<S, op_r_to_l, e> seg_r(N);

    for (int i = 0; i < N; i++)
    {
        auto [a, b] = ab[i];
        int pi = hld.get_pos(i);
        seg_l.set(pi, S(a, b)), seg_r.set(pi, S(a, b));
    }

    for (int q = 0; q < Q; q++)
    {
        int t;
        cin >> t;
        if (t == 0)
        {
            int p, c, d;
            cin >> p >> c >> d;
            seg_l.set(hld.get_pos(p), S(c, d)), seg_r.set(hld.get_pos(p), S(c, d));
        }

        if (t == 1)
        {
            int u, v, x;
            cin >> u >> v >> x;

            S ans = e();
            for (auto [l, r, is_reverse] : hld.get_path_ranges(u, v))
            {
                if (!is_reverse)
                {
                    ans = op_l_to_r(ans, seg_l.prod(l, r));
                }
                else
                {
                    ans = op_l_to_r(ans, seg_r.prod(l, r));
                }
            }
            cout << ans.f(x).val() << endl;
        }
    }

    return 0;
}