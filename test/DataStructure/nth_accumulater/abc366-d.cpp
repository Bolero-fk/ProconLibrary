// competitive-verifier: PROBLEM https://atcoder.jp/contests/abc366/tasks/abc366_d

#include "DataStructure/nth_accumulater.hpp"
#include <bits/stdc++.h>

using namespace std;

int main()
{
    int N;
    cin >> N;
    vector A(N, vector<vector<long long>>(N, vector<long long>(N)));
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            for (int k = 0; k < N; k++)
            {
                cin >> A[i][j][k];
            }
        }
    }

    nthAccumulater<long long, 3> accumulater(A);

    int Q;
    cin >> Q;
    for (int q = 0; q < Q; q++)
    {
        long long Lx, Rx, Ly, Ry, Lz, Rz;
        cin >> Lx >> Rx >> Ly >> Ry >> Lz >> Rz;
        Lx--, Ly--, Lz--;

        cout << accumulater.sum({Lx, Ly, Lz}, {Rx, Ry, Rz}) << endl;
    }

    return 0;
}