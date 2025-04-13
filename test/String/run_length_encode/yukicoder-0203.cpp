// competitive-verifier: PROBLEM https://yukicoder.me/problems/no/203

#include "String/run_length_encode.hpp"
#include <bits/stdc++.h>

using namespace std;

int main()
{
    string S1, S2;
    cin >> S1 >> S2;

    string S = S1 + S2;

    auto rle = run_length_encode(S);

    int ans = 0;
    for (auto [c, n] : rle)
    {
        if (c == 'o')
        {
            ans = max(ans, n);
        }
    }

    cout << ans << endl;

    return 0;
}