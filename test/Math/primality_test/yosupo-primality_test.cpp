// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/primality_test

#include "Math/primality_test.hpp"
#include <bits/stdc++.h>

using namespace std;

int main()
{
    long long Q;
    cin >> Q;

     for (int q = 0; q < Q; q++)
     {
         long long N;
         cin >> N;
         if (PrimalityTest::is_prime(N))
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