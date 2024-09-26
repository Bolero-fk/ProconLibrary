// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/pow_of_matrix

#include "Other/fast_power.hpp"
#include <bits/stdc++.h>
#include <atcoder/all>

using namespace std;

int main()
{
    long long N, K;
    cin >> N >> K;

    using S = vector<vector<atcoder::modint>>;
    auto mul = [&](S a, S b) -> S
    {
        S result(N, vector<atcoder::modint>(N));
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                for (int k = 0; k < N; k++)
                {
                    result[i][j] += a[i][k] * b[k][j];
                }
            }
        }

        return result;
    };

    auto e = [&]() -> S
    {
        S result = S(N, vector<atcoder::modint>(N));
        for (int i = 0; i < N; i++)
        {
            result[i][i] = 1;
        }

        return result;
    };

    vector a(N, vector<atcoder::modint>(N));
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            int in_a;
            cin >> in_a;
            a[i][j] = in_a;
        }
    }

    auto ans = fast_pow<S>(a, K, mul, e);
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cout << ans[i][j].val() << " \n"[j == N - 1];
        }
    }

    return 0;
}