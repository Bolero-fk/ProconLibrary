#include <bits/stdc++.h>
using namespace std;

template <class T = long long>
struct WeightedUnionFind
{
public:
    WeightedUnionFind() : _n(0) {}
    explicit WeightedUnionFind(int n, T e = 0) : _n(n), parent_or_size(n, -1), diff_weight(n, e) {}

    int merge(int a, int b, T w)
    {
        assert(0 <= a && a < _n);
        assert(0 <= b && b < _n);

        int x = leader(a), y = leader(b);
        if (x == y)
        {
            assert(diff(a, b) == w);
            return x;
        }

        w += weight(a), w -= weight(b);
        if (x == y)
        {
            return x;
        }
        if (-parent_or_size[x] < -parent_or_size[y])
        {
            swap(x, y), w *= -1;
        }
        parent_or_size[x] += parent_or_size[y];
        parent_or_size[y] = x;
        diff_weight[y] = w;
        return x;
    }

    bool same(int a, int b)
    {
        assert(0 <= a && a < _n);
        assert(0 <= b && b < _n);
        return leader(a) == leader(b);
    }

    int leader(int a)
    {
        assert(0 <= a && a < _n);
        if (parent_or_size[a] < 0)
        {
            return a;
        }
        int r = leader(parent_or_size[a]);
        diff_weight[a] += diff_weight[parent_or_size[a]];
        return parent_or_size[a] = r;
    }

    int size(int a)
    {
        assert(0 <= a && a < _n);
        return -parent_or_size[leader(a)];
    }

    T weight(int a)
    {
        leader(a);
        return diff_weight[a];
    }

    T diff(int a, int b)
    {
        return weight(b) - weight(a);
    }

    vector<vector<int>> groups()
    {
        vector<int> leader_buf(_n), group_size(_n);
        for (int i = 0; i < _n; i++)
        {
            leader_buf[i] = leader(i);
            group_size[leader_buf[i]]++;
        }
        vector<vector<int>> result(_n);
        for (int i = 0; i < _n; i++)
        {
            result[i].reserve(group_size[i]);
        }
        for (int i = 0; i < _n; i++)
        {
            result[leader_buf[i]].push_back(i);
        }
        result.erase(
            remove_if(result.begin(), result.end(),
                      [&](const vector<int> &v)
                      { return v.empty(); }),
            result.end());
        return result;
    }

private:
    int _n;
    vector<int> parent_or_size;
    vector<T> diff_weight;
};
