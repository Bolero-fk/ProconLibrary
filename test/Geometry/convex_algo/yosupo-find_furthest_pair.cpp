// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/furthest_pair

#include "Geometry/convex_algo/find_furthest_pair.hpp"
#include <bits/stdc++.h>

using namespace std;

void solve()
{
    int N;
    cin >> N;
    vector<Point<long long>> points;
    map<Point<long long>, vector<int>> to_id;
    for (int i = 0; i < N; i++)
    {
        long long x, y;
        cin >> x >> y;
        points.push_back(Point(x, y));
        to_id[Point(x, y)].push_back(i);
    }

    Convex convex(points);
    if (convex.get_ccw_points().size() <= 2)
    {
        int id1 = to_id.begin()->second.front();
        int id2 = to_id.rbegin()->second.back();

        cout << id1 << " " << id2 << endl;
        return;
    }

    auto [p1, p2] = convex_algo::find_furthest_pair(convex);
    cout << to_id[p1].front() << " " << to_id[p2].back() << endl;
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