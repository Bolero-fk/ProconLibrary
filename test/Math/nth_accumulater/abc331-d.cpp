// competitive-verifier: PROBLEM https://atcoder.jp/contests/abc331/tasks/abc331_d

#include "Math/nth_accumulater.hpp"
#include <bits/stdc++.h>

using namespace std;

int main()
{

    long long N, Q;
    cin >> N >> Q;

    vector<string> P(N);

    vector<vector<long long>> V(N, vector<long long>(N));
    for (int i = 0; i < N; i++)
    {
        cin >> P[i];
        for (int j = 0; j < N; j++)
        {
            if (P[i][j] == 'B')
            {
                V[i][j] = 1;
            }
        }
    }

    nthAccumulater<long long, 2> accumulater(V);

    for (int q = 0; q < Q; q++)
    {
        long long A, B, C, D;
        cin >> A >> B >> C >> D;
        C++, D++;

        cout << accumulater.cyclic_sum({A, B}, {C, D}) << endl;
    }

    return 0;
}