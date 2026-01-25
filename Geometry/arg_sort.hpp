#include <bits/stdc++.h>
using namespace std;

bool arg_comp(const pair<long long, long long> &p, const pair<long long, long long> &q)
{
    // (-pi, pi] の偏角順にするための分類：
    //  -1: theta <= 0（下半平面 + 正のx軸）
    //   0: 原点（角度0扱い）
    //  +1: theta > 0（上半平面 + 負のx軸(=pi)）
    auto sign = [](const pair<long long, long long> &p) -> int
    {
        if (p.first == 0 && p.second == 0)
            return 0;
        else if (p.second < 0 || (p.second <= 0 && p.first > 0))
            return -1;
        else
            return 1;
    };
    const int sp = sign(p), sq = sign(q);
    if (sp != sq)
    {
        return sp < sq;
    }

    // 同一グループ内は外積の符号で偏角順（反時計回りが先）
    auto cross = [](const pair<long long, long long> &p, const pair<long long, long long> &q) -> long long
    {
        return p.first * q.second - p.second * q.first;
    };
    return cross(p, q) > 0;
}
