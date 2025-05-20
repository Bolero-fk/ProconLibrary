#include <bits/stdc++.h>
using namespace std;

class HeavyLightDecomposition
{
public:
    HeavyLightDecomposition(int n)
        : n(n), edges(n), parent(n, -1), depth(n, 0), heavy(n, -1), head(n), pos(n), sz(n), built(false)
    {
    }

    void add_edge(int u, int v)
    {
        assert(0 <= u && u < n);
        assert(0 <= v && v < n);
        edges[u].push_back(v);
        edges[v].push_back(u);
    }

    void build(int root = 0)
    {
        assert(0 <= root && root < n);
        if (built)
        {
            return;
        }

        parent[root] = -1;
        depth[root] = 0;
        dfs_size(root);

        int time = 0;
        decompose(root, root, time);
        built = true;
    }

    vector<array<int, 2>> get_path_ranges(int u, int v)
    {
        assert(0 <= u && u < n);
        assert(0 <= v && v < n);
        ensure_built();

        vector<array<int, 2>> ranges;

        while (head[u] != head[v])
        {
            if (depth[head[v]] < depth[head[u]])
            {
                ranges.push_back({pos[head[u]], pos[u] + 1});
                u = parent[head[u]];
            }
            else
            {
                ranges.push_back({pos[head[v]], pos[v] + 1});
                v = parent[head[v]];
            }
        }

        if (depth[v] < depth[u])
        {
            swap(u, v);
        }

        ranges.push_back({pos[u], pos[v] + 1});
        return ranges;
    }

    array<int, 2> get_subtree_range(int u)
    {
        assert(0 <= u && u < n);

        ensure_built();
        return {pos[u], pos[u] + sz[u]};
    }

    int lca(int u, int v)
    {
        assert(0 <= u && u < n);
        assert(0 <= v && v < n);

        ensure_built();
        while (head[u] != head[v])
        {
            if (depth[head[u]] > depth[head[v]])
            {
                swap(u, v);
            }
            v = parent[head[v]];
        }
        return depth[u] < depth[v] ? u : v;
    }

    int get_pos(int v)
    {
        assert(0 <= v && v < n);

        ensure_built();
        return pos[v];
    }

    int get_parent(int v)
    {
        assert(0 <= v && v < n);

        ensure_built();
        return parent[v];
    }

    int get_subtree_size(int u)
    {
        assert(0 <= u && u < n);

        ensure_built();
        return sz[u];
    }

private:
    int n;
    vector<vector<int>> edges;
    vector<int> parent, depth, heavy, head, pos, sz;
    bool built;

    void ensure_built()
    {
        if (!built)
        {
            build();
        }
    }

    int dfs_size(int v)
    {
        sz[v] = 1;
        int max_size = 0;
        for (int u : edges[v])
        {
            if (u == parent[v])
            {
                continue;
            }

            parent[u] = v;
            depth[u] = depth[v] + 1;
            int sub = dfs_size(u);
            sz[v] += sub;
            if (max_size < sub)
            {
                max_size = sub;
                heavy[v] = u;
            }
        }

        return sz[v];
    }

    void decompose(int v, int h, int &time)
    {
        head[v] = h;
        pos[v] = time++;
        if (heavy[v] != -1)
        {
            decompose(heavy[v], h, time);
        }

        for (int u : edges[v])
        {
            if (u == parent[v] || u == heavy[v])
            {
                continue;
            }

            decompose(u, u, time);
        }
    }
};