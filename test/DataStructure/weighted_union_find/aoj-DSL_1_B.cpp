// competitive-verifier: PROBLEM https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_1_B

#include "DataStructure/weighted_union_find.hpp"
#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n, q;
    cin >> n >> q;

    WeightedUnionFind wuf(n);

    for (int i = 0; i < q; i++)
    {
        int t;
        cin >> t;
        if (t == 0)
        {
            int x, y, z;
            cin >> x >> y >> z;
            wuf.merge(x, y, z);
        }
        if (t == 1)
        {
            int x, y;
            cin >> x >> y;
            if (!wuf.same(x, y))
            {
                cout << "?" << endl;
            }
            else
            {
                cout << wuf.diff(x, y) << endl;
            }
        }
    }

    return 0;
}