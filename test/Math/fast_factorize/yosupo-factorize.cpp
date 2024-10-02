// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/factorize

#include <bits/stdc++.h>
using namespace std;

#include "Math/fast_factorizer.hpp"

int main()
{
    int Q;
    cin >> Q;

    for (int i = 0; i < Q; i++)
    {
        long long a;
        cin >> a;
        auto x = FastFactorizer::factorize(a);

        cout << x.size() << " ";
        for (auto n : x)
        {
            cout << n << " ";
        }
        cout << endl;
    }

    return 0;
}