// competitive-verifier: PROBLEM https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_4_B

#include "Geometry/convex_algo/find_furthest_pair.hpp"
#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n;
    cin >> n;

    vector<Point<long double>> points;
    for (int i = 0; i < n; i++)
    {
        long double x, y;
        cin >> x >> y;
        points.push_back(Point(x, y));
    }

    Convex convex(points, true);

    auto [p1, p2] = convex_algo::find_furthest_pair(convex);

    long double ans = sqrtl((p1 - p2).norm());
    cout << fixed << setprecision(12) << ans << endl;

    return 0;
}