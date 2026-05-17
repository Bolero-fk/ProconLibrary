// competitive-verifier: LOCALCASE ./cases/hom

#include "EnumerativeCombinatorics/combination_prime_mod.hpp"
#include <atcoder/modint>
#include <bits/stdc++.h>

using namespace std;

int main()
{
    int Q;
    cin >> Q;

    combinatorics<atcoder::modint998244353> comb(1e6);

    for (int q = 0; q < Q; q++)
    {
        int n, r;
        cin >> n >> r;
        cout << comb.H(n, r).val() << endl;
    }

    return 0;
}