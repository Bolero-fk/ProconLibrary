// competitive-verifier: PROBLEM https://yukicoder.me/problems/no/67
// competitive-verifier: ERROR 1e-9

#include "Other/binary_search.hpp"
#include <bits/stdc++.h>

using namespace std;

int main()
{
    int N;
    cin >> N;
    vector<double> L(N);
    for (int i = 0; i < N; i++)
    {
        cin >> L[i];
    }

    long long K;
    cin >> K;

    auto check = [&](double l) -> bool
    {
        long long cnt = 0;
        for (int i = 0; i < N; i++)
        {
            if (K <= floor(L[i] / l))
            {
                return true;
            }

            cnt += floor(L[i] / l);
        }

        return K <= cnt;
    };

    double ans = bin_search<double>(0, 1e9, check);
    cout << fixed << setprecision(15) << ans << endl;

    return 0;
}