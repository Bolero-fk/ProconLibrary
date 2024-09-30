// competitive-verifier: PROBLEM https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=NTL_1_B

#include "Math/mod_power.hpp"
#include <bits/stdc++.h>

using namespace std;

int main()
{
    long long m, n;
    cin >> m >> n;

    cout << mod_pow<long long>(m, n, 1000000007) << endl;

    return 0;
}