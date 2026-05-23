// competitive-verifier: LOCALCASE ./cases/perm

#include "EnumerativeCombinatorics/large_combinatorics_prime_mod.hpp"
#include <atcoder/modint>
#include <bits/stdc++.h>

using namespace std;

int main()
{
    int Q;
    cin >> Q;

    large_combinatorics<atcoder::modint998244353> comb;

    for (int q = 0; q < Q; q++)
    {
        int n, r;
        cin >> n >> r;
        cout << comb.P(n, r).val() << endl;
    }

    return 0;
}