#include "Geometry/convex.hpp"
#include <bits/stdc++.h>
using namespace std;

namespace convex_algo
{
    // ピックの定理を利用して凸多角形内部の格子点を数える関数
    // 内部格子点数 = (2 * 面積 - 辺上の格子点数 + 2) / 2
    template <class T, typename = enable_if_t<is_integral_v<T>>>
    long long count_inner_grid_points(const Convex<T> &convex)
    {
        assert(2 < convex.get_ccw_points().size());
        return (convex.get_twice_area() - count_on_grid_points(convex) + 2) / 2;
    }

    template <class T, typename = enable_if_t<is_integral_v<T>>>
    long long count_on_grid_points(const Convex<T> &convex)
    {
        assert(2 < convex.get_ccw_points().size());

        const auto &ccw_points = convex.get_ccw_points();
        long long cnt = 0;
        for (int i = 0; i < ccw_points.size(); i++)
        {
            const Point &a = ccw_points[i];
            const Point &b = ccw_points[(i + 1) % ccw_points.size()];
            cnt += gcd(abs(a.real() - b.real()), abs(a.imag() - b.imag()));
        }

        return cnt;
    }

    template <class T, typename = enable_if_t<is_integral_v<T>>>
    long long count_grid_points(const Convex<T> &convex)
    {
        assert(2 < convex.get_ccw_points().size());

        return count_inner_grid_points(convex) + count_on_grid_points(convex);
    }

}