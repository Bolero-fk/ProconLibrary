#include <bits/stdc++.h>
using namespace std;

template <typename Cost>
struct MinimusSteinerTree
{
    const Cost INF = numeric_limits<Cost>::max();
    using P = pair<Cost, int>;
    struct Edge
    {
        int to;
        Cost cost;
        Edge() {}
        Edge(int to, Cost cost) : to(to), cost(cost) {}
    };
    int n;
    vector<vector<Edge>> g;
    MinimusSteinerTree() {}
    MinimusSteinerTree(int n) : n(n), g(n) {}
    void addEdge(int a, int b, Cost cost)
    {
        g[a].emplace_back(b, cost);
    }

    pair<Cost, vector<array<int, 2>>> solve(const vector<int> &terminals)
    {
        const int K = terminals.size();
        vector dp(1 << K, vector<pair<Cost, vector<pair<int, int>>>>(n, {INF, {}}));
        for (int t = 0; t < K; t++)
        {
            dp[1 << t][terminals[t]].first = 0;
        }

        for (int S = 1; S < (1 << K); S++)
        {
            // Sの部分集合を頂点vを経由して結合するパターンを計算
            for (int T = (S - 1) & S; T > 0; T = (T - 1) & S)
            {
                for (int v = 0; v < n; v++)
                {
                    if (dp[T][v].first == INF || dp[S ^ T][v].first == INF)
                    {
                        continue;
                    }

                    if (dp[T][v].first + dp[S ^ T][v].first < dp[S][v].first)
                    {
                        dp[S][v].first = dp[T][v].first + dp[S ^ T][v].first;
                        dp[S][v].second = {{T, v}, {S ^ T, v}};
                    }
                }
            }

            // 集合Sから到達できる状態を計算
            priority_queue<P, vector<P>, greater<P>> pq;
            for (int u = 0; u < n; u++)
            {
                if (dp[S][u].first != INF)
                {
                    pq.push({dp[S][u].first, u});
                }
            }

            while (pq.size())
            {
                auto [dist, u] = pq.top();
                pq.pop();
                if (dp[S][u].first < dist)
                {
                    continue;
                }

                for (auto [v, cost] : g[u])
                {
                    if (dist + cost < dp[S][v].first)
                    {
                        dp[S][v].first = dist + cost;
                        dp[S][v].second = {{S, u}};
                        pq.push({dp[S][v].first, v});
                    }
                }
            }
        }

        if (dp.back()[terminals[0]].first == INF)
        {
            return {};
        }

        // 復元する
        queue<pair<int, int>> qu;
        qu.push({(1 << K) - 1, terminals[0]});

        vector<array<int, 2>> edges;

        while (qu.size())
        {
            auto [S, u] = qu.front();
            qu.pop();

            for (auto [next_S, v] : dp[S][u].second)
            {
                qu.push({next_S, v});

                if (u != v)
                {
                    edges.push_back({u, v});
                }
            }
        }

        return {dp.back()[terminals[0]].first, edges};
    }
};
