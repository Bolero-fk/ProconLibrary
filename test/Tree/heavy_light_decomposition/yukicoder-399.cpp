// competitive-verifier: PROBLEM https://yukicoder.me/problems/no/399

#include "Tree/heavy_light_decomposition.hpp"
#include <atcoder/lazysegtree>
#include <bits/stdc++.h>
using namespace std;

struct S
{
    long long value;
    int size;
};
using F = long long;

S op(S a, S b) { return {a.value + b.value, a.size + b.size}; }
S e() { return {0, 0}; }
S mapping(F f, S x) { return {x.value + f * x.size, x.size}; }
F composition(F f, F g) { return f + g; }
F id() { return 0; }

int main()
{
    int N;
    cin >> N;

    HeavyLightDecomposition hld(N);

    for (int i = 0; i < N - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        hld.add_edge(u - 1, v - 1);
    }

    atcoder::lazy_segtree<S, op, e, F, mapping, composition, id> seg(vector<S>(N, {1, 1}));

    int Q;
    cin >> Q;

    long long ans = 0;

    for (int i = 0; i < Q; i++)
    {
        int A, B;
        cin >> A >> B;
        A--, B--;

        auto ranges = hld.get_path_ranges(A, B);
        S sum = e();
        for (auto [l, r, _] : ranges)
        {
            sum = op(sum, seg.prod(l, r));
            seg.apply(l, r, 1);
        }

        ans += sum.value;
    }

    cout << ans << endl;

    return 0;
}