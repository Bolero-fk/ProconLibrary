// competitive-verifier: PROBLEM https://atcoder.jp/contests/typical90/tasks/typical90_bf
// competitive-verifier: IGNORE
// testcase id is different from url

#include "Tree/doubling.hpp"
#include <bits/stdc++.h>

using namespace std;

int main()
{
    long long N, K;
    cin >> N >> K;

    Doubling graph(100000, K);

    for (int x = 0; x < 100000; x++)
    {
        long long y = 0;
        string S = to_string(x);
        for (auto c : S)
        {
            y += c - '0';
        }

        long long z = (x + y) % 100000;
        graph.add_edge(x, z, 0);
    }

    cout << graph.step_forward(N, K).first << endl;

    return 0;
}