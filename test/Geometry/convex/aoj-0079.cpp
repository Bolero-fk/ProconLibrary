// competitive-verifier: PROBLEM https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0079

#include "Geometry/convex.hpp"
#include <bits/stdc++.h>

using namespace std;
int main()
{

    vector<Point<long double>> points;

    string line;
    while (getline(cin, line))
    {
        if (line.empty())
            continue;

        stringstream ss(line);

        long double x, y;
        char comma;
        ss >> x >> comma >> y;

        points.push_back(Point(x, y));
    }

    Convex convex(points);

    long double ans = convex.get_twice_area() / 2;

    cout << fixed << setprecision(6) << ans << endl;

    return 0;
}