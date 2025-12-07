// competitive-verifier: PROBLEM https://yukicoder.me/problems/no/674

#include "DataStructure/interval_set.hpp"
#include <bits/stdc++.h>

using namespace std;

int main()
{
    long long D, Q;
    cin >> D >> Q;

    IntervalSet<long long> interval_set;

    long long ans = 0;
    for (int i = 0; i < Q; i++)
    {
        long long A, B;
        cin >> A >> B;

        auto [l, r] = interval_set.add_interval(A, B + 1);
        ans = max(ans, r - l);
        cout << ans << endl;
    }

    return 0;
}