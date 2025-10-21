// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/0002

#include "Math/digits_base_10.hpp"
#include <bits/stdc++.h>

using namespace std;

int main()
{
    int a, b;
    while (scanf("%d %d", &a, &b) != EOF)
    {
        cout << digits_base_10(a + b) << endl;
    }
}
