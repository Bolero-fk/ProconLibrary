// competitive-verifier: PROBLEM https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_C
// competitive-verifier: ERROR 0.000001

#include "Geometry/integer_line.hpp"
#include <bits/stdc++.h>

using namespace std;

int main()
{
    long long x1, y1, x2, y2, x3, y3;
    cin >> x1 >> y1;
    cin >> x2 >> y2;
    cin >> x3 >> y3;

    const IntegerLine::Point p1 = {x1, y1};
    const IntegerLine::Point p2 = {x2, y2};
    const IntegerLine::Point p3 = {x3, y3};

    const IntegerLine bisector1 = IntegerLine::perpendicular_bisector(p1, p2);

    const IntegerLine bisector2 = IntegerLine::perpendicular_bisector(p1, p3);

    const optional<IntegerLine::Intersection> intersection = bisector1.intersection(bisector2);

    assert(intersection.has_value());

    const auto [xNumerator, yNumerator, denominator] = intersection.value();

    const long double centerX = static_cast<long double>(xNumerator) / static_cast<long double>(denominator);
    const long double centerY = static_cast<long double>(yNumerator) / static_cast<long double>(denominator);

    const long double dx = centerX - x1;
    const long double dy = centerY - y1;
    const long double radius = sqrt(dx * dx + dy * dy);

    cout << fixed << setprecision(15) << centerX << " " << centerY << " " << radius << endl;

    return 0;
}