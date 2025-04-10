// competitive-verifier: PROBLEM https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_4_A

#include "Geometry/convex.hpp"
#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n;
    cin >> n;

    vector<Point<int>> points;
    for (int i = 0; i < n; i++)
    {
        int x, y;
        cin >> x >> y;
        points.push_back(Point(x, y));
    }

    Convex convex(points, true);

    const vector<Point<int>> ccw_points = convex.get_ccw_points();

    int start_i = 0;
    for (int i = 1; i < ccw_points.size(); i++)
    {
        Point p1 = ccw_points[start_i];
        Point p2 = ccw_points[i];
        if (p1.imag() != p2.imag() && p2.imag() < p1.imag())
        {
            start_i = i;
        }
        else if (p1.imag() == p2.imag() && p2.real() < p1.real())
        {
            start_i = i;
        }
    }

    cout << ccw_points.size() << endl;
    for (int i = 0; i < ccw_points.size(); i++)
    {
        Point p = ccw_points[(start_i + i) % ccw_points.size()];
        cout << p.real() << " " << p.imag() << endl;
    }

    return 0;
}