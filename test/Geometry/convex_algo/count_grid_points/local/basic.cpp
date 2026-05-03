// competitive-verifier: LOCALCASE ./cases/basic

#include <bits/stdc++.h>
using namespace std;

#include "Geometry/convex_algo/count_grid_points.hpp"

int main()
{
    int T;
    cin >> T;

    while (T--)
    {
        int N;
        cin >> N;

        vector<Point<long long>> points(N);
        for (int i = 0; i < N; i++)
        {
            long long x, y;
            cin >> x >> y;
            points[i] = Point<long long>(x, y);
        }

        Convex<long long> convex(points);

        long long inner = convex_algo::count_inner_grid_points(convex);
        long long on = convex_algo::count_on_grid_points(convex);
        long long total = convex_algo::count_grid_points(convex);

        cout << inner << ' ' << on << ' ' << total << '\n';
    }

    return 0;
}