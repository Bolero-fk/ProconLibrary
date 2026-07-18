// competitive-verifier: PROBLEM https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_2_C

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

        const optional<IntegerLine::Intersection> intersection = line1.intersection(line2);

        assert(intersection.has_value());

        const auto [xNumerator, yNumerator, denominator] = intersection.value();

        const long double x = static_cast<long double>(xNumerator) / static_cast<long double>(denominator);

        const long double y = static_cast<long double>(yNumerator) / static_cast<long double>(denominator);

        cout << fixed << setprecision(10) << x << " " << y << endl;
    }

    return 0;
}