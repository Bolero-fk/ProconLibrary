// competitive-verifier: PROBLEM https://www.hackerrank.com/contests/magic-lines-july-2015/challenges/run-length-encoding

#include "String/run_length_encode.hpp"
#include <bits/stdc++.h>

using namespace std;

int main()
{
    string S;
    cin >> S;

    auto rle = run_length_encode(S);

    string ans;
    for (auto [c, n] : rle)
    {
        ans += c + to_string(n);
    }

    cout << ans;

    return 0;
}