#include <bits/stdc++.h>
using namespace std;

template <typename T, typename Compare = std::less<T>>
    requires std::strict_weak_order<Compare, T, T>
class IntervalSet
{
private:
    // すべての区間長の合計
    T sum_length = 0;

    // 互いに交差しない半開区間 [first, second) の集合
    set<pair<T, T>> intervals;

    // 点 x を含む区間のイテレータ（なければ end）
    typename set<pair<T, T>>::const_iterator
    find_interval(const T &x) const
    {
        // first >= x となる最初の区間
        auto itr = intervals.lower_bound({x, x});

        // ひとつ左だけ、x を含みうる
        if (itr != intervals.begin())
        {
            auto prev_itr = prev(itr);
            if (prev_itr->first <= x && x < prev_itr->second)
                return prev_itr;
        }

        // ぴったり x から始まる区間
        if (itr != intervals.end() && itr->first <= x && x < itr->second)
            return itr;

        return intervals.end();
    }

public:
    IntervalSet() {}

    // [L, R) を追加し、必要なら隣接区間とマージする
    pair<T, T> add_interval(const T &L, const T &R)
    {
        return add_interval({L, R});
    }

    // [L, R) を追加し、必要なら隣接区間とマージする
    pair<T, T> add_interval(const pair<T, T> &LR)
    {
        assert(LR.first < LR.second);

        auto [l, r] = LR;

        // first >= l となる最初の区間
        auto itr = intervals.lower_bound(LR);

        // 左側に 1 つだけ重なりうる区間を見る
        if (itr != intervals.begin())
        {
            auto prev_itr = prev(itr);
            if (prev_itr->second >= l)
            {
                l = min(l, prev_itr->first);
                r = max(r, prev_itr->second);

                sum_length -= abs(prev_itr->second - prev_itr->first);
                itr = intervals.erase(prev_itr);
            }
        }

        // 先頭が r 以下の区間をすべてマージ
        while (itr != intervals.end() && itr->first <= r)
        {
            l = min(l, itr->first);
            r = max(r, itr->second);

            sum_length -= abs(itr->second - itr->first);
            itr = intervals.erase(itr);
        }

        intervals.insert({l, r});
        sum_length += abs(r - l);

        return {l, r};
    }

    // 区間集合から [L, R) を削除（集合としての差）
    void erase_interval(const T &L, const T &R)
    {
        erase_interval({L, R});
    }

    // 区間集合から [L, R) を削除（集合としての差）
    void erase_interval(const std::pair<T, T> &LR)
    {
        assert(LR.first < LR.second);

        const auto [l, r] = LR;
        if (intervals.empty())
            return;

        // first >= l となる最初の区間
        auto itr = intervals.lower_bound(LR);

        // 左側に 1 つだけ、[l, r) と交差しうる区間を見る
        if (itr != intervals.begin())
        {
            auto prev_itr = prev(itr);
            const auto [a, b] = *prev_itr;

            // [a, b) と [l, r) が交差
            if (b > l && a < r)
            {
                itr = intervals.erase(prev_itr);
                sum_length -= abs(b - a);

                if (a < l)
                {
                    sum_length += abs(l - a);
                    intervals.insert({a, l});
                }
                if (r < b)
                {
                    sum_length += abs(b - r);
                    intervals.insert({r, b});
                }
            }
        }

        // ここから先は first >= l が保証されている
        while (itr != intervals.end())
        {
            const auto [a, b] = *itr;

            if (a >= r)
                break; // これ以降は交差しない

            if (b <= r)
            {
                // 完全に [l, r) に含まれる区間
                itr = intervals.erase(itr);
                sum_length -= abs(b - a);
            }
            else
            {
                // a < r < b →右側 [r, b) だけ残す
                intervals.erase(itr);
                intervals.insert({r, b});
                sum_length -= abs(b - a);
                sum_length += abs(b - r);
                break;
            }
        }
    }

    // u と v が同じ区間に属するか
    bool same(T u, T v) const
    {
        if (intervals.empty())
            return false;

        if (v < u)
            swap(u, v);

        auto itr = find_interval(u);
        if (itr == intervals.end())
            return false;

        return v < itr->second;
    }

    // u が属する区間の長さ（なければ 0）
    T length(const T &u) const
    {
        auto itr = find_interval(u);
        if (itr == intervals.end())
            return T(0);
        return itr->second - itr->first;
    }

    // すべての区間長の合計
    T get_sum_lentgth() const
    {
        return sum_length;
    }

    void print() const
    {
        for (auto [l, r] : intervals)
        {
            cout << "[" << l << ", " << r << ") ";
        }
        cout << '\n';
    }
};