#include <bits/stdc++.h>
#include <atcoder/segtree>
using namespace std;

class BracketRangeQuery
{
    struct S
    {
        int matched;
        int open;
        int close;
    };

    static S op(S a, S b)
    {
        int x = min(a.open, b.close);
        return {
            a.matched + b.matched + x,
            a.open + b.open - x,
            a.close + b.close - x,
        };
    }

    static S e()
    {
        return {0, 0, 0};
    }

    using seg_t = atcoder::segtree<S, op, e>;

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
        seg.set(i, make_node(c));
        s[i] = c;
    }

    // [l, r) が正しい括弧列か？
    bool is_valid(int l, int r)
    {
        assert(0 <= l && l <= r && r <= n);
        S x = seg.prod(l, r);
        return x.open == 0 && x.close == 0;
    }

    // [l, r) で正しく対応付けられる括弧ペアの最大数
    int count_matched_pairs(int l, int r)
    {
        assert(0 <= l && l <= r && r <= n);
        return seg.prod(l, r).matched;
    }

    const string &str() const { return s; }

private:
    int n;
    string s;
    seg_t seg;

    static S make_node(char c)
    {
        if (c == '(')
            return {0, 1, 0};
        if (c == ')')
            return {0, 0, 1};
        return {0, 0, 0}; // 括弧以外は寄与なし
    }

    void init(const string &s_)
    {
        s = s_;
        n = (int)s.size();

        vector<S> v(n);
        for (int i = 0; i < n; ++i)
        {
            v[i] = make_node(s[i]);
        }

        seg = seg_t(v);
    }
};