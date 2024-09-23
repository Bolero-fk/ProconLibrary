#include <bits/stdc++.h>
using namespace std;

#include <Heuristic/fast_random_engine.hpp>

// 参考 https://future-architect.github.io/articles/20211201a/
template <typename T>
class ApproxTspSolver
{
    vector<vector<pair<T, int>>> cost_table;

    T double_bridge(vector<int> &nexts, vector<int> &prevs, const vector<vector<T>> &costs)
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

        vector<int> x(nexts.size());
        for (int i = 0; i < nexts.size(); i++)
        {
            x[i] = nexts[x[i]];
        }

        unordered_set<int> used;
        vector<int> swaps;

        shuffle_vector(random_ids);

        for (auto random_id : random_ids)
        {
            if (used.contains(random_id) || used.contains((random_id + 1) % N))
            {
                continue;
            }

            used.insert(random_id);
            used.insert((random_id + 1) % N);

            swaps.push_back(random_id);
            if (swaps.size() == 4)
            {
                break;
            }
        }

        if (swaps.size() != 4)
        {
            return 0;
        }

        sort(swaps.begin(), swaps.end());

        vector<int> u(4), v(4);
        for (int i = 0; i < 4; i++)
        {
            u[i] = x[swaps[i]], v[i] = nexts[u[i]];
        }

        T diff_cost = 0;
        for (int i = 0; i < 4; i++)
        {
            diff_cost -= costs[u[i]][v[i]];
        }

        for (int i = 0; i < 4; i++)
        {
            nexts[u[i]] = v[(i + 2) % 4];
            prevs[v[(i + 2) % 4]] = u[i];
        }

        for (int i = 0; i < 4; i++)
        {
            diff_cost += costs[u[i]][v[(i + 2) % 4]];
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

    T two_opt(vector<int> &nexts, vector<int> &prevs, const vector<vector<T>> &costs)
    {
        int N = nexts.size();
        if (nexts.size() < 4)
        {
            return 0;
        }

        T diff_cost = 0;

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
    pair<T, vector<int>> solve(const vector<int> &x, const vector<vector<T>> &costs)
    {
        int N = x.size();

        // i番目の前後の頂点が何番かを管理する
        vector<int> nexts(x.size()), prevs(x.size());
        for (int i = 0; i < x.size(); i++)
        {
            nexts[i] = (i + 1) % x.size();
            prevs[i] = (i - 1 + x.size()) % x.size();
        }

        cost_table = vector(N, vector<pair<T, int>>());
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

            T diff_score = 0;
            diff_score += double_bridge(nexts, prevs, costs);
            diff_score += two_opt(nexts, prevs, costs);

            if (diff_score < 0)
            {
                global_nexts = nexts, global_prevs = prevs;
            }
        }

        vector<int> result_path = {global_nexts.back()};
        while (result_path.back() != (int)x.size() - 1)
        {
            result_path.push_back(global_nexts[result_path.back()]);
        }

        T result_cost = 0;
        for (int i = 0; i < N; i++)
        {
            result_cost += costs[result_path[i]][result_path[(i + 1) % N]];
        }

        return pair(result_cost, result_path);
    }
};