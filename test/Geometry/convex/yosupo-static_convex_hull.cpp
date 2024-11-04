// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/static_convex_hull

#include "Geometry/convex.hpp"
#include <bits/stdc++.h>

using namespace std;

void solve()
{
    int N;
    cin >> N;
    vector<Point<long long>> points;
    for (int i = 0; i < N; i++)
    {
        long long x, y;
        cin >> x >> y;
        points.push_back(Point(x, y));
    }

    Convex convex(points);
    vector<Point<long long>> ccw_points = convex.get_ccw_points();
    cout << ccw_points.size() << endl;
    for (auto point : ccw_points)
    {
        cout << point.real() << " " << point.imag() << endl;
    }
}

int main()
{
    int T;
    cin >> T;

    for (int i = 0; i < T; i++)
    {
        solve();
    }

    return 0;
}