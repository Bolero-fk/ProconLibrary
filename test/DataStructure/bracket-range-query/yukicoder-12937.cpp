// competitive-verifier: PROBLEM https://yukicoder.me/problems/12937

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
        int t;
        cin >> t;
        if (t == 1)
        {
            int p;
            char c;
            cin >> p >> c;
            brq.set(p - 1, c);
        }
        if (t == 2)
        {
            int l, r;
            cin >> l >> r;
            bool ans = brq.is_valid(l - 1, r);
            if (ans)
            {
                cout << "Yes" << endl;
            }
            else
            {
                cout << "No" << endl;
            }
        }
    }

    return 0;
}