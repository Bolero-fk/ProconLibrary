// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/binomial_coefficient_prime_mod

#include "EnumerativeCombinatorics/binomial_coefficient_prime_mod.hpp"
#include <atcoder/modint>
#include <bits/stdc++.h>

using namespace std;

using mint = atcoder::modint;

int main()
{
    int T, m;
    cin >> T >> m;

    mint::set_mod(m);

    combination<atcoder::modint> comb(min(m, 10000000) - 1);

    for (int i = 0; i < T; i++)
    {
        int n, k;
        cin >> n >> k;
        cout << comb(n, k).val() << endl;
    }

    return 0;
}