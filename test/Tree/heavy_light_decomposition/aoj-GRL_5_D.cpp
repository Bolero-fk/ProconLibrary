// competitive-verifier: PROBLEM https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_D

#include "Tree/heavy_light_decomposition.hpp"
#include <atcoder/segtree>
#include <bits/stdc++.h>
using namespace std;

using S = long long;
S op(S a, S b) { return a + b; }
S e() { return 0; }

int main()
{
    int n;
    cin >> n;

    HeavyLightDecomposition hld(n + n - 1);
    int edge_cnt = 0;
    for (int i = 0; i < n; i++)
    {
        int k;
        cin >> k;
        for (int j = 0; j < k; j++)
        {
            int c;
            cin >> c;
            hld.add_edge(i, n + edge_cnt);
            hld.add_edge(n + edge_cnt, c);
            edge_cnt++;
        }
    }

    atcoder::segtree<S, op, e> seg(n + n - 1);

    int q;
    cin >> q;

    for (int i = 0; i < q; i++)
    {
        int T;
        cin >> T;

        if (T == 0)
        {
            int v, w;
            cin >> v >> w;
            int ei = hld.get_pos(hld.get_parent(v));
            seg.set(ei, seg.get(ei) + w);
        }

        if (T == 1)
        {
            int u;
            cin >> u;

            auto ranges = hld.get_path_ranges(0, u);
            S ans = e();
            for (auto [l, r] : ranges)
            {
                ans = op(ans, seg.prod(l, r));
            }
            cout << ans << endl;
        }
    }

    return 0;
};