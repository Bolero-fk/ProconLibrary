// competitive-verifier: PROBLEM https://atcoder.jp/contests/abc250/tasks/abc250_e

#include "Hash/zobrist_hash.hpp"
#include <bits/stdc++.h>

using namespace std;

int main()
{
    int N;
    cin >> N;

    vector<long long> a(N), b(N);
    for (int i = 0; i < N; i++)
    {
        cin >> a[i];
    }

    for (int i = 0; i < N; i++)
    {
        cin >> b[i];
    }

    ZobristHash hashed_a(a, ZobristHash::HASH_TYPE::TYPE);
    ZobristHash hashed_b(b, ZobristHash::HASH_TYPE::TYPE);

    int Q;
    cin >> Q;

    for (int i = 0; i < Q; i++)
    {
        int x, y;
        cin >> x >> y;

        if (hashed_a.get_accumulate_hash(0, x) == hashed_b.get_accumulate_hash(0, y))
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