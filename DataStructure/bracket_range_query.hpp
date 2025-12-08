#include <bits/stdc++.h>
#include "atcoder/lazysegtree"
using namespace std;

class BracketRangeQuery
{
    using S = int;
    using F = int;

    static constexpr int INF = (int)1e9;

    static S op(S a, S b) { return min(a, b); }
    static S e() { return INF; }

    static S mapping(F f, S x)
    {
        return x == INF ? INF : x + f;
    }

    static F composition(F f, F g)
    {
        return f + g;
    }

    static F id() { return 0; }

    using seg_t = atcoder::lazy_segtree<S, op, e, F, mapping, composition, id>;

public:
    BracketRangeQuery() : n(0), seg() {}

    explicit BracketRangeQuery(const string &s_)
    {
        init(s_);
    }

    explicit BracketRangeQuery(int n_)
    {
        init(string(n_, '?'));
    }

    // i 文字目を c に変更
    void set(int i, char c)
    {
        assert(0 <= i && i < n);
        seg.apply(i + 1, n + 1, conv(c) - conv(s[i]));
        s[i] = c;
    }

    // [l, r) が正しい括弧列か？
    bool is_valid(int l, int r)
    {
        assert(0 <= l && l <= r && r <= n);

        int base = seg.get(l);
        int right = seg.get(r);

        if (right - base != 0)
            return false;
        if (l == r)
            return true;

        int mn = seg.prod(l + 1, r + 1);
        return mn >= base;
    }

    const string &str() const { return s; }

private:
    int n;
    string s;
    seg_t seg;

    static int conv(char c)
    {
        if (c == '(')
            return +1;
        if (c == ')')
            return -1;
        return 0; // 括弧以外は寄与なし
    }

    void init(const string &s_)
    {
        s = s_;
        n = (int)s.size();
        vector<S> pref(n + 1);
        pref[0] = 0;
        for (int i = 0; i < n; ++i)
        {
            pref[i + 1] = pref[i] + conv(s[i]);
        }
        seg = seg_t(pref);
    }
};