// competitive-verifier: PROBLEM https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_2_A

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

        if (line1.is_parallel(line2))
        {
            cout << 2 << endl;
        }
        else if (line1.is_perpendicular(line2))
        {
            cout << 1 << endl;
        }
        else
        {
            cout << 0 << endl;
        }
    }

    return 0;
}