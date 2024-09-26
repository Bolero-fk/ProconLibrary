// competitive-verifier: PROBLEM https://atcoder.jp/contests/abc367/tasks/abc367_f

#include "Hash/zobrist_hash.hpp"
#include <bits/stdc++.h>

using namespace std;

int main()
{
    int N, Q;
    cin >> N >> Q;
    vector<long long> A(N), B(N);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
    }

    for (int i = 0; i < N; i++)
    {
        cin >> B[i];
    }

    ZobristHash hashA(A, ZobristHash::HASH_TYPE::COUNT);
    ZobristHash hashB(B, ZobristHash::HASH_TYPE::COUNT);

    for (int i = 0; i < Q; i++)
    {
        int l, r, L, R;
        cin >> l >> r >> L >> R;
        l--, L--;

        if (hashA.get_accumulate_hash(l, r) == hashB.get_accumulate_hash(L, R))
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