// competitive-verifier: PROBLEM https://atcoder.jp/contests/abc167/tasks/abc167_d

#include "Tree/doubling.hpp"
#include <bits/stdc++.h>

using namespace std;

int main()
{
    long long N, K;
    cin >> N >> K;

    Doubling<long long> graph(N, K);

    vector<int> A(N);
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
        graph.add_edge(i, A[i] - 1, 0);
    }

    int ans = graph.step_forward(0, K).first;
    cout << ans + 1 << endl;

    return 0;
}