#include "Geometry/convex.hpp"
#include <bits/stdc++.h>
using namespace std;

namespace convex_algo
{
    enum class PointPosition
    {
        OUT = -1,
        ON = 0,
        IN = 1
    };

    template <class T, typename = enable_if_t<is_arithmetic_v<T>>>
    PointPosition contains_point(const Convex<T> &convex, const Point<T> &point)
    {
        using CCWResult = typename Point<T>::CCWResult;

        if (convex.has_point(point))
        {
            return PointPosition::ON;
        }

        if (!convex.is_inside_bounding_box(point))
        {
            return PointPosition::OUT;
        }

        const auto upper_itr = convex.get_upper_hull().upper_bound(point);
        const auto lower_itr = convex.get_lower_hull().upper_bound(point);

        CCWResult upper_ccw = Point<T>::ccw(*prev(upper_itr), *upper_itr, point);
        CCWResult lower_ccw = Point<T>::ccw(*prev(lower_itr), *lower_itr, point);
        if (upper_ccw == CCWResult::ON_SEGMENT || lower_ccw == CCWResult::ON_SEGMENT)
        {
            return PointPosition::ON;
        }

        if (upper_ccw == CCWResult::CLOCKWISE && lower_ccw == CCWResult::COUNTER_CLOCKWISE)
        {
            return PointPosition::IN;
        }

        return PointPosition::OUT;
    }
}