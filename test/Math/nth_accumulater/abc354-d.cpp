// competitive-verifier: PROBLEM https://atcoder.jp/contests/abc354/tasks/abc354_d

#include "Math/nth_accumulater.hpp"
#include <bits/stdc++.h>

using namespace std;

int main()
{
    long long A, B, C, D;
    cin >> A >> B >> C >> D;

    nthAccumulater<long long, 2> accumulater({{2, 1, 0, 1}, {1, 2, 1, 0}});
    cout << accumulater.cyclic_sum({B, A}, {D, C}) << endl;

    return 0;
}