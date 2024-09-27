#include <bits/stdc++.h>
using namespace std;

#include "Tree/doubling.hpp"
#include "Other/binary_search.hpp"

class LCA
{
    int N;
    int bit_width;
    vector<vector<int>> edges;
    vector<int> depth;
    Doubling<int_fast8_t> doubling;
    bool done_initialized = false;

    void dfs(int now, int parent)
    {
        if (parent != -1)
        {
            doubling.add_edge(now, parent, 0);
            depth[now] = depth[parent] + 1;
        }

        for (int next : edges[now])
        {
            if (next == parent)
            {
                continue;
            }

            dfs(next, now);
        }
    }

public:
    LCA(int N) : N(N)
    {
        bit_width = std::bit_width((unsigned int)N);
        doubling = Doubling<int_fast8_t>(N, N);
        edges.resize(N);
        depth = vector<int>(N, -1);
    };

    void add_edge(int u, int v)
    {
        edges[u].push_back(v);
    }

    void init(int root = 0)
    {
        depth[root] = 0;
        doubling.add_edge(root, root, 0);
        dfs(root, -1);
        done_initialized = true;
    }

    int find(int u, int v)
    {
        if (!done_initialized)
        {
            init();
        }

        if (depth[u] < depth[v])
        {
            swap(u, v);
        }

        // 深さを同じにする
        u = doubling.step_forward(u, depth[u] - depth[v]).first;
        if (u == v)
        {
            return u;
        }

        for (int bit = bit_width - 1; bit >= 0; bit--)
        {
            int next_u = doubling.step_forward(u, 1 << bit).first, next_v = doubling.step_forward(v, 1 << bit).first;
            if (next_u != next_v)
            {
                u = next_u, v = next_v;
            }
        }

        return doubling.step_forward(u, 1).first;
    }

    int dist(int u, int v) { return depth[u] + depth[v] - 2 * depth[find(u, v)]; }
};