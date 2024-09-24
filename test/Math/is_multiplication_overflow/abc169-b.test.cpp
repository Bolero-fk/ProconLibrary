// competitive-verifier: PROBLEM https://atcoder.jp/contests/abc169/tasks/abc169_b

#include "Math/is_multiplication_overflow.hpp"
#include <bits/stdc++.h>

using namespace std;

int main()
{
    long long N;
    cin >> N;

    vector<long long> A(N);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
    }
    sort(A.begin(), A.end());

    long long LIMIT = 1000000000000000000;
    long long ans = 1;
    for (int i = 0; i < N; i++)
    {
        if (!is_multiplication_overflow(ans, A[i], LIMIT))
        {
            ans = ans * A[i];
        }
        else
        {
            ans = -1;
            break;
        }
    }

    cout << ans << endl;

    return 0;
}