#include <bits/stdc++.h>
using namespace std;

template <typename T = long long>
class Doubling
{
    int N, L;

    vector<pair<int, T>> nexts;
    vector<vector<pair<int, T>>> parents;
    bool done_initialized = false;

public:
    Doubling() {};

    Doubling(int N, unsigned long long max_k) : N(N)
    {
        L = max<int>(bit_width(max_k), 1);
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

    vector<pair<int, T>> step_forwards(const vector<int> &indeces, unsigned long long k)
    {
        if (!done_initialized)
        {
            init();
        }

        vector<pair<int, T>> result(indeces.size());
        for (int i = 0; i < indeces.size(); i++)
        {
            result[i].first = indeces[i];
        }

        T sum_cost = 0;
        while (k != 0)
        {
            int bit_i = countr_zero(k);
            for (pair<int, T> &p : result)
            {
                p.second += parents[p.first][bit_i].second, p.first = parents[p.first][bit_i].first;
            }
            k ^= 1ll << bit_i;
        }

        return result;
    }

    // vを始点にK回移動した先のノードを返します
    pair<int, T> step_forward(int v, unsigned long long k)
    {
        return step_forwards({v}, k)[0];
    }

    vector<pair<int, T>> step_forwards(unsigned long long k)
    {
        vector<int> indeces;
        for (int i = 0; i < N; i++)
        {
            indeces.push_back(i);
        }

        return step_forwards(indeces, k);
    }
};