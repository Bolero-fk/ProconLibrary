// competitive-verifier: PROBLEM https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_1_C

#include "Geometry/point.hpp"
#include <bits/stdc++.h>

using namespace std;

int main()
{
    long long xp0, yp0, xp1, yp1;
    cin >> xp0 >> yp0 >> xp1 >> yp1;
    Point<long long> p0(xp0, yp0), p1(xp1, yp1);

    int q;
    cin >> q;

    for (int i = 0; i < q; i++)
    {
        long long xpi, ypi;
        cin >> xpi >> ypi;
        Point<long long> pi(xpi, ypi);

        Point<long long>::CCWResult ccw = Point<long long>::ccw(p0, p1, pi);
        if (ccw == Point<long long>::CCWResult::COUNTER_CLOCKWISE)
        {
            cout << "COUNTER_CLOCKWISE" << endl;
        }
        else if (ccw == Point<long long>::CCWResult::CLOCKWISE)
        {
            cout << "CLOCKWISE" << endl;
        }
        else if (ccw == Point<long long>::CCWResult::ON_LINE_BACK)
        {
            cout << "ONLINE_BACK" << endl;
        }
        else if (ccw == Point<long long>::CCWResult::ON_LINE_FRONT)
        {
            cout << "ONLINE_FRONT" << endl;
        }
        else if (ccw == Point<long long>::CCWResult::ON_SEGMENT)
        {
            cout << "ON_SEGMENT" << endl;
        }
    }

    return 0;
}