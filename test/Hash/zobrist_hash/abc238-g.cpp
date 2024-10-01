// competitive-verifier: PROBLEM https://atcoder.jp/contests/abc238/tasks/abc238_g

#include "Hash/zobrist_cubic_hash.hpp"
#include <bits/stdc++.h>

using namespace std;

int main()
{
    int N, Q;
    cin >> N >> Q;
    vector<long long> A(N);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
    }

    ZobristCubicHash hashA(A);

    for (int i = 0; i < Q; i++)
    {
        int L, R;
        cin >> L >> R;
        L--;

        if (hashA.get_range_hash(L, R) == 0)
        {
            cout << "Yes" << endl;
        }
        else
        {
            cout << "No" << endl;
        }
    }

    return 0;
}