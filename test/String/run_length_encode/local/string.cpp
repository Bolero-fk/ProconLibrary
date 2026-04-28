// competitive-verifier: LOCALCASE ./cases/string

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