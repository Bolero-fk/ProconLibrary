// competitive-verifier: PROBLEM https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_C

#include "DataStructure/kd_tree.hpp"
#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n;
    cin >> n;

    vector<array<int, 2>> p(n);
    for (int i = 0; i < n; i++)
    {
        cin >> p[i][0] >> p[i][1];
    }

    KDTree<int, 2> kd_tree(p);
    int q;
    cin >> q;

    for (int i = 0; i < q; i++)
    {
        int sx, tx, sy, ty;
        cin >> sx >> tx >> sy >> ty;

        auto result = kd_tree.range_search({sx, sy}, {tx, ty});
        sort(result.begin(), result.end(), [](const auto a, const auto b) -> bool
             { return a.id < b.id; });
        for (auto n : result)
        {
            cout << n.id << endl;
        }
        cout << endl;
    }

    return 0;
}