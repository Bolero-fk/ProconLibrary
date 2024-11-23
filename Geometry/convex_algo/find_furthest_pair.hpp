#include "Geometry/convex.hpp"
#include <bits/stdc++.h>
using namespace std;

namespace convex_algo
{
    template <class T, typename = enable_if_t<is_arithmetic_v<T>>>
    pair<Point<T>, Point<T>> find_furthest_pair(const Convex<T> &convex)
    {
        const vector<Point<T>> &ccw_points = convex.get_ccw_points();

        assert(2 < ccw_points.size());

        int left = distance(ccw_points.begin(), min_element(ccw_points.begin(), ccw_points.end()));
        int right = distance(ccw_points.begin(), max_element(ccw_points.begin(), ccw_points.end()));

        pair<Point<T>, Point<T>> result;
        T max_dist = 0;

        int i = left, j = right;
        do
        {
            T dist = (ccw_points[i] - ccw_points[j]).norm();
            if (max_dist < dist)
            {
                max_dist = dist;
                result = pair(ccw_points[i], ccw_points[j]);
            }

            // i の次の点と j の次の点を見比べ、i と j が反時計回りに回るように更新
            int next_i = (i + 1) % ccw_points.size(), next_j = (j + 1) % ccw_points.size();
            if (Point<T>::cross(ccw_points[next_i] - ccw_points[i], ccw_points[next_j] - ccw_points[j]) < 0)
            {
                i = next_i;
            }
            else
            {
                j = next_j;
            }
        } while (i != left || j != right);
        return result;
    }
}