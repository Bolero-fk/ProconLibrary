// competitive-verifier: PROBLEM https://yukicoder.me/problems/no/1641

#include "Tree/heavy_light_decomposition.hpp"
#include <atcoder/segtree>
#include <bits/stdc++.h>
using namespace std;

using S = int;
S op(S a, S b) { return a ^ b; }
S e() { return 0; }

int main()
{
    int N, Q;
    cin >> N >> Q;

    vector<int> C(N);
    for (int i = 0; i < N; i++)
    {
        cin >> C[i];
    }

    HeavyLightDecomposition hld(N);
    for (int i = 0; i < N - 1; i++)
    {
        int a, b;
        cin >> a >> b;
        hld.add_edge(a - 1, b - 1);
    }

    atcoder::segtree<S, op, e> seg(N);
    for (int i = 0; i < N; i++)
    {
        seg.set(hld.get_pos(i), C[i]);
    }

    for (int q = 0; q < Q; q++)
    {
        int T, x, y;
        cin >> T >> x >> y;
        x--;
        if (T == 1)
        {
            int xi = hld.get_pos(x);
            seg.set(xi, seg.get(xi) ^ y);
        }

        if (T == 2)
        {
            auto [l, r] = hld.get_subtree_range(x);
            cout << seg.prod(l, r) << endl;
        }
    }

    return 0;
};