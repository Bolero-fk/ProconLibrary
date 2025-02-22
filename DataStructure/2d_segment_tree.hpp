#include <bits/stdc++.h>
using namespace std;

// 二次元セグメント木
// ACLを基に作った
template <class S, auto op, auto e>
struct segtree2d
{
    static_assert(is_convertible_v<decltype(op), function<S(S, S)>>,
                  "op must work as S(S, S)");
    static_assert(is_convertible_v<decltype(e), function<S()>>,
                  "e must work as S()");

public:
    segtree2d() : segtree2d(0) {}
    explicit segtree2d(int h, int w)
    {
        init(h, w);
    }

    explicit segtree2d(const vector<vector<S>> &v)
    {
        init(v.size(), v[0].size());

        for (int i = 0; i < _h; i++)
        {
            for (int j = 0; j < _w; j++)
            {
                values[id(size_h + i, size_w + j)] = v[id(i, j)];
            }
        }

        for (int w = size_w; w < size_w * 2; w++)
        {
            for (int h = size_h - 1; h >= 1; h--)
            {
                update_h(h, w);
            }
        }

        for (int h = 0; h < size_h * 2; h++)
        {
            for (int w = size_w - 1; w >= 1; w--)
            {
                update_w(h, w);
            }
        }
    }

    void set(int p_h, int p_w, S x)
    {
        assert(0 <= p_h && p_h < _h);
        assert(0 <= p_w && p_w < _w);

        p_h += size_h;
        p_w += size_w;

        values[id(p_h, p_w)] = x;

        for (int i = p_h >> 1; i; i >>= 1)
        {
            update_h(i, p_w);
        }

        for (; p_h; p_h >>= 1)
        {
            for (int j = p_w >> 1; j; j >>= 1)
            {
                update_w(p_h, j);
            }
        }
    }

    S get(int p_h, int p_w) const
    {
        assert(0 <= p_h && p_h < _h);
        assert(0 <= p_w && p_w < _w);

        return values[id(p_h + size_h, p_w + size_w)];
    }

    S prod(int t, int l, int d, int r) const
    {
        assert(0 <= t && t <= d && t <= _h);
        assert(0 <= l && l <= r && r <= _w);

        S smt = e(), smd = e();
        t += size_h;
        d += size_h;
        l += size_w;
        r += size_w;

        for (; t < d; t >>= 1, d >>= 1)
        {
            if (t & 1)
                smt = op(smt, inner_prod(t++, l, r));
            if (d & 1)
                smd = op(inner_prod(--d, l, r), smd);
        }

        return op(smt, smd);
    }

private:
    int _n, size_h, size_w;
    int _h, _w;
    vector<S> values;

    void init(int h, int w)
    {
        _h = h;
        _w = w;
        size_h = (int)bit_ceil((unsigned int)(_h));
        size_w = (int)bit_ceil((unsigned int)(_w));

        values = vector<S>(size_h * size_w * 4, e());
    }

    int id(int h, int w) const
    {
        return h * 2 * size_w + w;
    }

    void update_h(int h, int w)
    {
        values[id(h, w)] = op(values[id(2 * h, w)], values[id(2 * h + 1, w)]);
    }

    void update_w(int h, int w)
    {
        values[id(h, w)] = op(values[id(h, 2 * w)], values[id(h, 2 * w + 1)]);
    }

    S inner_prod(int h, int l, int r) const
    {
        S sml = e(), smr = e();

        for (; l < r; l >>= 1, r >>= 1)
        {
            if (l & 1)
                sml = op(sml, values[id(h, l++)]);
            if (r & 1)
                smr = op(values[id(h, --r)], smr);
        }

        return op(sml, smr);
    }
};
