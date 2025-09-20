#include <bits/stdc++.h>
using namespace std;

#include "Heuristic/fast_random_engine.hpp"

namespace approx_tsp
{
    // ---------------------
    // 距離関数オブジェクト
    // ---------------------
    struct Euclidean
    {
        using CostType = double;
        template <typename T, size_t D>
        double operator()(const array<T, D> &a, const array<T, D> &b) const
        {
            CostType sum = 0;
            for (size_t i = 0; i < D; i++)
            {
                CostType d = a[i] - b[i];
                sum += d * d;
            }
            return sqrt(sum);
        }
    };

    struct Manhattan
    {
        using CostType = int;
        template <typename T, size_t D>
        CostType operator()(const array<T, D> &a, const array<T, D> &b) const
        {
            CostType sum = 0;
            for (size_t i = 0; i < D; i++)
            {
                sum += abs(a[i] - b[i]);
            }
            return sum;
        }
    };

    // ---------------------
    // パスモード列挙型
    // ---------------------
    enum class PathMode
    {
        Closed, // 1周する必要がある 1 → 2　→ ...　→ N　→ 1
        Open    // 1周する必要がない 1 → 2　→ ...　→ N
    };

    // 参考 https://future-architect.github.io/articles/20211201a/
    template <
        typename Distance = Euclidean,
        PathMode Mode = PathMode::Closed>
    class ApproxTspSolver
    {
        using CostType = Distance::CostType;
        Distance dist;

        vector<vector<pair<CostType, int>>> cost_table;

        CostType double_bridge(vector<int> &nexts, vector<int> &prevs, const vector<vector<CostType>> &costs)
        {
            int N = nexts.size();
            if (nexts.size() < 8)
            {
                return 0;
            }

            static vector<int> random_ids;
            if (random_ids.size() != nexts.size())
            {
                random_ids = nexts;
            }

            shuffle_vector(random_ids);

            unordered_set<int> used;
            array<array<int, 2>, 4> bridge_edges;

            int bridge_cnt = 0;
            // ダブルブリッジするidを8つ選ぶ。 これは隣接する2項を4つ選ぶ。
            for (auto curr : random_ids)
            {
                int next = nexts[curr];

                if (used.contains(curr) || used.contains(next))
                {
                    continue;
                }

                used.insert(curr), used.insert(next);

                bridge_edges[bridge_cnt++] = {curr, next};
                if (bridge_cnt == 4)
                {
                    break;
                }
            }

            if (bridge_cnt != 4)
            {
                return 0;
            }

            vector<int> order(N);
            int now = 0;
            for (int i = 0; i < N; i++)
            {
                order[now] = i;
                now = nexts[now];
            }

            sort(bridge_edges.begin(), bridge_edges.end(), [&](const array<int, 2> &a, const array<int, 2> &b) -> bool
                 { return order[a[0]] < order[b[0]]; });

            CostType diff_cost = 0;
            for (int i = 0; i < 4; i++)
            {
                diff_cost -= costs[bridge_edges[i][0]][bridge_edges[i][1]];
            }

            for (int i = 0; i < 4; i++)
            {
                nexts[bridge_edges[i][0]] = bridge_edges[(i + 2) % 4][1];
                prevs[bridge_edges[(i + 2) % 4][1]] = bridge_edges[i][0];
            }

            for (int i = 0; i < 4; i++)
            {
                diff_cost += costs[bridge_edges[i][0]][bridge_edges[(i + 2) % 4][1]];
            }

            return diff_cost;
        }

        // l ~ r までの向きを逆にする(lとrは含まない)
        void reverse_node(vector<int> &nexts, vector<int> &prevs, int l, int r)
        {
            nexts[r] = prevs[r];
            int now = nexts[r];
            while (now != l)
            {
                swap(nexts[now], prevs[now]);
                now = nexts[now];
            }
            prevs[l] = nexts[l];
        }

        CostType two_opt(vector<int> &nexts, vector<int> &prevs, const vector<vector<CostType>> &costs)
        {
            int N = nexts.size();
            if (nexts.size() < 4)
            {
                return 0;
            }

            CostType diff_cost = 0;

            auto try_swap = [&](int u1, int u2) -> bool
            {
                for (auto [cost, u3] : cost_table[u1])
                {
                    int u4 = nexts[u3];
                    if (u2 == u3)
                    {
                        break;
                    }
                    if (costs[u1][u2] + costs[u3][u4] <= costs[u1][u3] + costs[u2][u4])
                    {
                        continue;
                    }

                    diff_cost -= costs[u1][u2], diff_cost -= costs[u3][u4];
                    diff_cost -= costs[u2][nexts[u2]], diff_cost -= costs[u3][prevs[u3]];

                    reverse_node(nexts, prevs, u2, u3);
                    nexts[u1] = u3, prevs[u3] = u1;
                    nexts[u2] = u4, prevs[u4] = u2;

                    diff_cost += costs[u1][u3], diff_cost += costs[u2][u4];
                    diff_cost += costs[u3][nexts[u3]], diff_cost += costs[u2][prevs[u2]];

                    return true;
                }

                for (auto [cost, u4] : cost_table[u2])
                {
                    int u3 = prevs[u4];
                    if (u1 == u4)
                    {
                        break;
                    }
                    if (costs[u1][u2] + costs[u3][u4] <= costs[u1][u3] + costs[u2][u4])
                    {
                        continue;
                    }

                    diff_cost -= costs[u1][u2], diff_cost -= costs[u3][u4];
                    diff_cost -= costs[u2][nexts[u2]], diff_cost -= costs[u3][prevs[u3]];

                    reverse_node(nexts, prevs, u2, u3);
                    nexts[u1] = u3, prevs[u3] = u1;
                    nexts[u2] = u4, prevs[u4] = u2;

                    diff_cost += costs[u1][u3], diff_cost += costs[u2][u4];
                    diff_cost += costs[u3][nexts[u3]], diff_cost += costs[u2][prevs[u2]];

                    return true;
                }

                return false;
            };

            while (true)
            {
                bool update = false;
                for (int u1 = 0; u1 < N; u1++)
                {
                    int u2 = nexts[u1];

                    if (try_swap(u1, u2))
                    {
                        update = true;
                        break;
                    }
                }

                if (!update)
                {
                    break;
                }
            }

            return diff_cost;
        }

    public:
        template <typename PointType, size_t D>
        pair<CostType, vector<int>> solve(const vector<array<PointType, D>> &points, int start = -1, int end = -1)
        {
            const int N = points.size();
            const int M = (Mode == PathMode::Closed ? N : N + 1);

            vector costs(M, vector<CostType>(M));

            for (int i = 0; i < N; i++)
            {
                for (int j = 0; j < N; j++)
                {
                    if (i == j)
                    {
                        continue;
                    }

                    costs[i][j] = dist(points[i], points[j]);
                }
            }

            if (start != -1 || end != -1)
            {
                if (start != -1 && end != -1)
                {
                    for (int i = 0; i < N; i++)
                    {
                        if (i == start || i == end)
                        {
                            continue;
                        }

                        costs[i][N] = 1e8;
                        costs[N][i] = 1e8;
                    }
                }
                else
                {
                    assert(false);
                }
            }

            return solve(costs);
        }

        pair<CostType, vector<int>> solve(const vector<vector<CostType>> &costs)
        {
            int N = costs.size();

            // i番目の前後の頂点が何番かを管理する
            vector<int> nexts(N), prevs(N);
            for (int i = 0; i < N; i++)
            {
                nexts[i] = (i + 1) % N;
                prevs[i] = (i - 1 + N) % N;
            }

            cost_table = vector(N, vector<pair<CostType, int>>());
            for (int i = 0; i < N; i++)
            {
                for (int j = 0; j < N; j++)
                {
                    if (i == j)
                    {
                        continue;
                    }
                    cost_table[i].push_back(pair(costs[i][j], j));
                }
                sort(cost_table[i].begin(), cost_table[i].end());
            }

            vector<int> global_nexts = nexts, global_prevs = prevs;
            for (int i = 0; i < 100; i++)
            {
                nexts = global_nexts, prevs = global_prevs;

                CostType diff_score = 0;
                diff_score += double_bridge(nexts, prevs, costs);
                diff_score += two_opt(nexts, prevs, costs);

                if (diff_score < 0)
                {
                    global_nexts = nexts, global_prevs = prevs;
                }
            }

            vector<int> result_path = {global_nexts.back()};
            while (result_path.back() != N - 1)
            {
                result_path.push_back(global_nexts[result_path.back()]);
            }

            if constexpr (Mode == PathMode::Open)
            {
                result_path.pop_back();
            }

            CostType result_cost = 0;
            for (int i = 0; i < (int)result_path.size() - 1; i++)
            {
                result_cost += costs[result_path[i]][result_path[i + 1]];
            }

            if constexpr (Mode == PathMode::Closed)
            {
                result_cost += costs[result_path.back()][result_path.front()];
            }

            return pair(result_cost, result_path);
        }
    };
}
