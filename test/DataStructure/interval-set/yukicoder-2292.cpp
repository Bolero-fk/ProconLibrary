// competitive-verifier: PROBLEM https://yukicoder.me/problems/no/2292

#include "DataStructure/interval_set.hpp"
#include <bits/stdc++.h>

using namespace std;

int main()
{
    int N, Q;
    cin >> N >> Q;

    IntervalSet<int> interval_set;

    // 閉区間なので二倍して帳尻を合わせる
    for (int i = 0; i < Q; i++)
    {
        int t;
        cin >> t;
        if (t == 1)
        {
            int L, R;
            cin >> L >> R;
            interval_set.add_interval(2 * L, 2 * R + 1);
        }
        if (t == 2)
        {
            int L, R;
            cin >> L >> R;
            interval_set.erase_interval(2 * L + 1, 2 * R);
        }
        if (t == 3)
        {
            int u, v;
            cin >> u >> v;
            // cout << "!!!: " << t << " " << u << " " << v << endl;
            cout << ((u == v) || interval_set.same(2 * u, 2 * v)) << endl;
        }
        if (t == 4)
        {
            int u;
            cin >> u;
            int len = interval_set.length(2 * u) / 2 + 1;
            // cout << "!!!: " << t << " " << u << " " << len << endl;
            cout << len << endl;
        }

        // interval_set.print();
    }

    return 0;
}