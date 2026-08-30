// competitive-verifier: PROBLEM https://yukicoder.me/problems/no/3652

#include "DataStructure/bracket_range_query.hpp"
#include <bits/stdc++.h>

using namespace std;

int main()
{
    int N, Q;
    cin >> N >> Q;
    string S;
    cin >> S;

    BracketRangeQuery brq(S);

    for (int i = 0; i < Q; i++)
    {
        int ti;
        cin >> ti;
        if (ti == 1)
        {
            int x, t;
            cin >> x >> t;
            if (t == 1)
            {
                brq.set(x - 1, '(');
            }
            else
            {
                brq.set(x - 1, ')');
            }
        }
        if (ti == 2)
        {
            int l, r;
            cin >> l >> r;
            int match_cnt = brq.count_matched_pairs(l - 1, r);
            cout << 2 * match_cnt << endl;
        }
    }

    return 0;
}