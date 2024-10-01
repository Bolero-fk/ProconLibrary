// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/static_range_sum

#include "DataStructure/nth_accumulater.hpp"
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

    nthAccumulater<long long, 1> accumulater(A);

    for (int q = 0; q < Q; q++)
    {
        int l, r;
        cin >> l >> r;
        cout << accumulater.sum({l}, {r}) << endl;
    }

    return 0;
}