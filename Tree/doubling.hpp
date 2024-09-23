template <typename T = long long>
class Doubling
{
    int N, L;

    vector<pair<int, T>> nexts;
    vector<vector<pair<int, T>>> parents;
    bool done_initialized = false;

public:
    Doubling(int N, unsigned long long max_k) : N(N)
    {
        L = bit_width(max_k);
        nexts = vector<pair<int, T>>(N, {-1, 0});
        parents = vector<vector<pair<int, T>>>(N + 1, vector<pair<int, T>>(L, {-1, 0}));
    }

    void add_edge(int from, int to, T cost)
    {
        if (nexts[from].first != -1)
        {
            assert(false);
        }

        nexts[from] = pair(to, cost);
    }

    void init()
    {
        for (int i = 0; i < N; i++)
        {
            parents[i][0] = nexts[i];
        }

        for (int i = 0; i < L - 1; i++)
        {
            for (int v = 0; v < N; v++)
            {
                auto p1 = parents[v][i];
                auto p2 = parents[p1.first][i];
                parents[v][i + 1] = pair(p2.first, p1.second + p2.second);
            }
        }

        done_initialized = true;
    }

    // vを始点にK回移動した先のノードを返します
    pair<int, T> step_forward(int v, unsigned long long k)
    {
        if (!done_initialized)
        {
            init();
        }

        T sum_cost = 0;

        for (int i = L - 1; i >= 0; --i)
        {
            unsigned long long len = 1ull << i;
            if (k >= len)
            {
                k -= len, sum_cost += parents[v][i].second, v = parents[v][i].first;
            }
        }

        return pair(v, sum_cost);
    }
};
