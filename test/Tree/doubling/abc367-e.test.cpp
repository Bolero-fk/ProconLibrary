#define PROBLEM "https://atcoder.jp/contests/abc367/tasks/abc367_e"

#include <Tree/doubling.hpp>
#include <bits/stdc++.h>

using namespace std;

int main()
{
    long long N, K;
    cin >> N >> K;
    vector<long long> X(N), A(N);

    Doubling graph(N, K);
    for (int i = 0; i < N; i++)
    {
        cin >> X[i];
        graph.add_edge(i, X[i] - 1, 0);
    }

    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
    }

    for (int i = 0; i < N; i++)
    {
        cout << A[graph.step_forward(i, K).first] << " ";
    }
    cout << endl;

    return 0;
}