// competitive-verifier: PROBLEM https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1068

#include "DataStructure/2d_segment_tree.hpp"
#include <bits/stdc++.h>

using namespace std;

long long op(long long a, long long b)
{
    return min(a, b);
}

long long e()
{
    return LONG_LONG_MAX;
}

void solve(int r, int c, int q)
{
    segtree2d<long long, op, e> seg(r, c);
    for (int h = 0; h < r; h++)
    {
        for (int w = 0; w < c; w++)
        {
            long long grid;
            cin >> grid;
            seg.set(h, w, grid);
        }
    }

    for (int Q = 0; Q < q; Q++)
    {
        int r1, c1, r2, c2;
        cin >> r1 >> c1 >> r2 >> c2;

        int ans = seg.prod(r1, c1, r2 + 1, c2 + 1);
        cout << ans << endl;
    }
}

int main()
{

    while (true)
    {
        int r, c, q;
        cin >> r >> c >> q;
        if (r == 0 && c == 0 && q == 0)
        {
            break;
        }

        solve(r, c, q);
    }

    return 0;
}