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

    /*
    const vector<Point<int>> ccw_points = convex.ccw_points;

    cout << convex.ccw_points.size() << endl;

    int start_i = 0;
    for (int i = 1; i < convex.ccw_points.size(); i++)
    {
        Point p1 = convex.ccw_points[start_i];
        Point p2 = convex.ccw_points[i];
        if (p1.imag() != p2.imag() && p2.imag() < p1.imag())
        {
            start_i = i;
        }
        else if (p1.imag() == p2.imag() && p2.real() < p1.real())
        {
            start_i = i;
        }
    }

    for (int i = 0; i < convex.ccw_points.size(); i++)
    {
        Point p = convex.ccw_points[(start_i + i) % convex.ccw_points.size()];
        cout << p.real() << " " << p.imag() << endl;
    }*/

    return 0;
}