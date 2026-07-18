// competitive-verifier: PROBLEM https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_2_B

#include "Geometry/integer_line.hpp"
#include <bits/stdc++.h>

using namespace std;

int main()
{
    int q;
    cin >> q;

    while (q--)
    {
        long long x0, y0, x1, y1;
        long long x2, y2, x3, y3;
        cin >> x0 >> y0 >> x1 >> y1;
        cin >> x2 >> y2 >> x3 >> y3;

        const IntegerLine::Point p0 = {x0, y0};
        const IntegerLine::Point p1 = {x1, y1};
        const IntegerLine::Point p2 = {x2, y2};
        const IntegerLine::Point p3 = {x3, y3};

        const IntegerLine line1 = IntegerLine::through(p0, p1);
        const IntegerLine line2 = IntegerLine::through(p2, p3);

        bool intersects;

        if (line1.is_same(line2))
        {
            // 同一直線上では、2線分の範囲が重なるかを判定する。
            const bool overlapX =
                max(min(p0.first, p1.first), min(p2.first, p3.first)) <= min(max(p0.first, p1.first), max(p2.first, p3.first));

            const bool overlapY =
                max(min(p0.second, p1.second), min(p2.second, p3.second)) <= min(max(p0.second, p1.second), max(p2.second, p3.second));

            intersects = overlapX && overlapY;
        }
        else if (line1.is_parallel(line2))
        {
            intersects = false;
        }
        else
        {
            // 各線分の端点が、もう一方の直線をまたぐか、
            // またはいずれかの端点が直線上にあれば交差する。
            const bool segment2CrossesLine1 =
                !line1.same_side(p2, p3);

            const bool segment1CrossesLine2 =
                line2.opposite_side(p0, p1) || line2.contains(p0) || line2.contains(p1);

            intersects =
                segment2CrossesLine1 && segment1CrossesLine2;
        }

        cout << (intersects ? 1 : 0) << endl;
    }

    return 0;
}