// competitive-verifier: PROBLEM https://atcoder.jp/contests/abc300/tasks/abc300_f
// competitive-verifier: IGNORE
// AtCoder's test cases are now private.

#include "Other/binary_search.hpp"
#include "DataStructure/nth_accumulater.hpp"
#include <bits/stdc++.h>

using namespace std;

int main()
{
    long long N, M, K;
    cin >> N >> M >> K;
    string S;
    cin >> S;

    vector<int> x_cnt(N);
    for (int i = 0; i < N; i++)
    {
        if (S[i] == 'x')
        {
            x_cnt[i]++;
        }
    }

    nthAccumulater<long long, 1> nth_accumulator(x_cnt);
    long long ans = 0;
    for (int l = 0; l < N; l++)
    {
        auto check = [&](long long r) -> bool
        {
            return nth_accumulator.cyclic_sum({l}, {r}) <= K;
        };

        long long max_r = bin_search<long long>(l, N * M + 1, check);
        long long len = max_r - l;
        ans = max(ans, len);
    }

    cout << ans << endl;

    return 0;
}