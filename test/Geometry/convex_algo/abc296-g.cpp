// competitive-verifier: PROBLEM https://atcoder.jp/contests/abc296/tasks/abc296_g

#include "Geometry/convex_algo/contains_point.hpp"
#include <bits/stdc++.h>

using namespace std;
int main()
{
    int N;
    cin >> N;
    vector<Point<long long>> points;
    for (int i = 0; i < N; i++)
    {
        long long X, Y;
        cin >> X >> Y;
        points.push_back(Point(X, Y));
    }

    Convex convex(points);

    int Q;
    cin >> Q;
    for (int i = 0; i < Q; i++)
    {
        long long A, B;
        cin >> A >> B;

        convex_algo::PointPosition result = convex_algo::contains_point(convex, Point(A, B));
        if (result == convex_algo::PointPosition::OUT)
        {
            cout << "OUT" << endl;
        }
        if (result == convex_algo::PointPosition::ON)
        {
            cout << "ON" << endl;
        }
        if (result == convex_algo::PointPosition::IN)
        {
            cout << "IN" << endl;
        }
    }

    return 0;
}