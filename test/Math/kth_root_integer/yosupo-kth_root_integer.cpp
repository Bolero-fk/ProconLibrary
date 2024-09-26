// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/kth_root_integer

#include "Math/kth_root_integer.hpp"
#include <bits/stdc++.h>

using namespace std;

int main()
{
    int T;
    cin >> T;
    for (int i = 0; i < T; i++)
    {
        unsigned long long A, K;
        cin >> A >> K;
        cout << kth_root(A, K) << endl;
    }

    return 0;
}