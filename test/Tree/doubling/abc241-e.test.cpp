// competitive-verifier: PROBLEM https://atcoder.jp/contests/abc241/tasks/abc241_e
// competitive-verifier: IGNORE
// AtCoder's test cases are now private.

#include "Tree/doubling.hpp"
#include <bits/stdc++.h>

using namespace std;

int main()
{
    long long N, K;
    cin >> N >> K;
    vector<long long> A(N);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
    }

    Doubling graph(N, K);

    for (int i = 0; i < N; i++)
    {
        graph.add_edge(i, (i + A[i]) % N, A[i]);
    }

    auto ans = graph.step_forward(0, K);
    cout << ans.second << endl;

    return 0;
}