// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/unionfind_with_potential

#include "DataStructure/weighted_union_find.hpp"
#include <bits/stdc++.h>
#include <atcoder/all>

using namespace std;

int main()
{
    int N, Q;
    cin >> N >> Q;

    WeightedUnionFind<atcoder::modint998244353> wuf(N);

    for (int i = 0; i < Q; i++)
    {
        int t;
        cin >> t;
        if (t == 0)
        {
            int u, v, x;
            cin >> u >> v >> x;
            if (wuf.valid(u, v, x))
            {
                wuf.merge(u, v, x);
            }

            cout << wuf.valid(u, v, x) << endl;
        }
        if (t == 1)
        {
            int x, y;
            cin >> x >> y;
            if (!wuf.same(x, y))
            {
                cout << "-1" << endl;
            }
            else
            {
                cout << wuf.diff(x, y).val() << endl;
            }
        }
    }

    return 0;
}