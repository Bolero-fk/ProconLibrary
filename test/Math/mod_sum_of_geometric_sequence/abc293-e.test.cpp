#define PROBLEM "https://atcoder.jp/contests/abc293/tasks/abc293_e"

#include <Math/mod_sum_of_geometric_sequence.hpp>
#include <atcoder/modint>
#include <bits/stdc++.h>

using namespace std;

int main()
{
    long long A, X, M;
    cin >> A >> X >> M;

    atcoder::modint::set_mod(M);
    atcoder::modint ans = sum_of_geometric_sequence<atcoder::modint>(1, A, X);

    cout << ans.val() << endl;

    return 0;
}