#include "Geometry/point.hpp"
#include <bits/stdc++.h>
using namespace std;

template <class T, typename = enable_if_t<is_arithmetic_v<T>>>
class Convex
{
    using CCWResult = typename Point<T>::CCWResult;

    vector<Point<T>> ccw_points;
    set<Point<T>> upper_hull;
    set<Point<T>> lower_hull;
    bool allow_on_line;
    T twice_area = 0;

    Point<T> bounding_box_min, bounding_box_max;

    T calculate_twice_area()
    {
        assert(3 <= ccw_points.size());

        T result = 0;
        for (int i = 0; i < ccw_points.size(); i++)
        {
            const Point<T> &p = ccw_points[i];
            const Point<T> &next_p = ccw_points[(i + 1) % ccw_points.size()];
            result += Point<T>::cross(p, next_p);
        }

        return result;
    }

    list<Point<T>> build_half_hull(const set<Point<T>> &points, bool upper)
    {
        assert(3 <= points.size());

        CCWResult ccw_direction = (upper ? CCWResult::CLOCKWISE : CCWResult::COUNTER_CLOCKWISE);

        list<Point<T>> half_hull;
        for (auto &p3 : points)
        {
            if (half_hull.size() < 2)
            {
                half_hull.push_back(p3);
                continue;
            }

            while (half_hull.size() >= 2)
            {
                auto p2 = half_hull.back();
                half_hull.pop_back();
                auto p1 = half_hull.back();

                CCWResult ccw_result = Point<T>::ccw(p1, p2, p3);
                bool is_valid_direction = (ccw_result == ccw_direction) || (allow_on_line && ccw_result == CCWResult::ON_LINE_FRONT);

                if (is_valid_direction)
                {
                    half_hull.push_back(p2);
                    break;
                }
            }
            half_hull.push_back(p3);
        }

        return half_hull;
    }

    vector<Point<T>> merge_hulls(const list<Point<T>> &upper_points, const list<Point<T>> &lower_points)
    {
        assert(2 <= upper_points.size() && 2 <= lower_points.size());

        vector<Point<T>> merged_hull(lower_points.begin(), lower_points.end());

        // lower_pointsの最後とupper_pointsの最初が重複するので取り除く
        merged_hull.pop_back();

        merged_hull.insert(merged_hull.end(), upper_points.rbegin(), upper_points.rend());

        // upper_pointsの最後とlower_pointsの最初が重複するので取り除く
        merged_hull.pop_back();

        return merged_hull;
    }

    void set_bounding_box()
    {
        assert(0 < ccw_points.size());
        const T MAX_INF = numeric_limits<T>::max();
        const T MIN_INF = numeric_limits<T>::lowest();

        T x_min = MAX_INF, y_min = MAX_INF, x_max = MIN_INF, y_max = MIN_INF;
        for (const auto &point : ccw_points)
        {
            x_min = min(x_min, point.real());
            y_min = min(y_min, point.imag());
            x_max = max(x_max, point.real());
            y_max = max(y_max, point.imag());
        }

        bounding_box_min = Point<T>(x_min, y_min);
        bounding_box_max = Point<T>(x_max, y_max);
    }

public:
    Convex(vector<Point<T>> points, bool allow_on_line = false) : allow_on_line(allow_on_line)
    {
        // 重複点の削除 + ソート
        set<Point<T>> point_st(points.begin(), points.end());

        if (point_st.size() < 2)
        {
            ccw_points = vector<Point<T>>(point_st.begin(), point_st.end());
            twice_area = 0;
            upper_hull = point_st;
            lower_hull = point_st;
            set_bounding_box();
            return;
        }

        list<Point<T>> upper_hull = build_half_hull(point_st, true);
        list<Point<T>> lower_hull = build_half_hull(point_st, false);

        this->ccw_points = merge_hulls(upper_hull, lower_hull);

        this->upper_hull = set<Point<T>>(upper_hull.begin(), upper_hull.end());
        this->lower_hull = set<Point<T>>(lower_hull.begin(), lower_hull.end());

        twice_area = calculate_twice_area();
        set_bounding_box();
    };

    bool has_point(const Point<T> &point) const
    {
        return upper_hull.contains(point) || lower_hull.contains(point);
    }

    bool is_inside_bounding_box(const Point<T> &point) const
    {
        return bounding_box_min.real() <= point.real() && point.real() <= bounding_box_max.real() &&
               bounding_box_min.imag() <= point.imag() && point.imag() <= bounding_box_max.imag();
    }

    const vector<Point<T>> &get_ccw_points() const
    {
        return ccw_points;
    }

    const T &get_twice_area() const
    {
        return twice_area;
    }

    const set<Point<T>> &get_upper_hull() const
    {
        return upper_hull;
    }

    const set<Point<T>> &get_lower_hull() const
    {
        return lower_hull;
    }
};