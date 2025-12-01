// competitive-verifier: PROBLEM https://yukicoder.me/problems/12925

#include "Hash/zobrist_parity_hash.hpp"
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

    ZobristParityHash zh(A);

    for (int q = 0; q < Q; q++)
    {
        int l1, r1, l2, r2;
        cin >> l1 >> r1 >> l2 >> r2;
        l1--, l2--;

        if (zh.get_range_hash(l1, r1) == zh.get_range_hash(l2, r2))
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