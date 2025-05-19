// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/minimum_steiner_tree

#include "Graph/minimum_steiner_tree.hpp"
#include <bits/stdc++.h>

using namespace std;

int main()
{
    int N, M;
    cin >> N >> M;

    MinimusSteinerTree<long long> graph(N);

    map<array<int, 2>, array<int, 2>> mp;
    for (int i = 0; i < M; i++)
    {
        int U, V, W;
        cin >> U >> V >> W;
        graph.addEdge(U, V, W), graph.addEdge(V, U, W);
        if (!mp.contains({U, V}))
        {
            mp[{U, V}] = {W, i}, mp[{V, U}] = {W, i};
        }
        else if (W < mp[{U, V}][0])
        {
            mp[{U, V}] = {W, i}, mp[{V, U}] = {W, i};
        }
    }

    int K;
    cin >> K;
    vector<int> X(K);
    for (int i = 0; i < K; i++)
    {
        cin >> X[i];
    }

    auto [Y, edges] = graph.solve(X);
    cout << Y << " " << edges.size() << endl;
    long long sum = 0;
    for (auto [U, V] : edges)
    {
        cout << mp[{U, V}][1] << " ";
    }
    cout << endl;

    return 0;
}