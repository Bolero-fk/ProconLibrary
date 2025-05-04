#include <bits/stdc++.h>
using namespace std;

template <typename T>
struct DifferenceConstraintsSolver
{
    struct Edge
    {
        int from, to;
        T cost;
        Edge(int from, int to, T cost) : from(from), to(to), cost(cost) {}
    };

    const T INF = numeric_limits<T>::max() / 2;
    int N;
    vector<Edge> edges;

    DifferenceConstraintsSolver(int n) : N(n) {}

    // 制約: x_i - x_j <= c を追加します。
    void add_leq_constraint(int i, int j, T c)
    {
        assert(0 <= i && i < N);
        assert(0 <= j && j < N);

        edges.emplace_back(j, i, c);
    }

    // 制約: x_i - x_j >= c を追加します。
    void add_geq_constraint(int i, int j, T c)
    {
        assert(0 <= i && i < N);
        assert(0 <= j && j < N);

        edges.emplace_back(i, j, -c);
    }

    // 制約: x_i - x_j == c を追加します。
    void add_eq_constraint(int i, int j, T c)
    {
        assert(0 <= i && i < N);
        assert(0 <= j && j < N);

        add_leq_constraint(i, j, c);
        add_geq_constraint(i, j, c);
    }

    pair<bool, vector<T>> solve(int S = 0)
    {
        assert(0 <= S && S < N);

        vector<T> result(N, INF);
        result[S] = 0;

        for (int iter = 0; iter < N - 1; ++iter)
        {
            for (const auto &e : edges)
            {
                if (result[e.from] != INF)
                {
                    result[e.to] = min(result[e.to], result[e.from] + e.cost);
                }
            }
        }

        for (const auto &e : edges)
        {
            if (result[e.from] != INF && result[e.to] > result[e.from] + e.cost)
            {
                return {false, {}};
            }
        }

        return {true, result};
    }
};