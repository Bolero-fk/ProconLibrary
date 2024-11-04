#include <bits/stdc++.h>
using namespace std;

template <class T, typename = enable_if_t<is_arithmetic_v<T>>>
class Point
{
    complex<T> coordinate;
    static constexpr long double EPS = 1e-8;

public:
    Point() {}

    Point(T x, T y) : coordinate(x, y) {}

    Point(complex<T> coordinate) : coordinate(coordinate) {}

    T real() const { return coordinate.real(); }
    T imag() const { return coordinate.imag(); }
    T norm() const { return std::norm(coordinate); }

    static T dot(const Point &a, const Point &b)
    {
        return a.real() * b.real() + a.imag() * b.imag();
    }

    static T cross(const Point &a, const Point &b)
    {
        return a.real() * b.imag() - a.imag() * b.real();
    }

    Point operator+(const Point &other) const
    {
        return Point(this->coordinate + other.coordinate);
    }

    Point operator-(const Point &other) const
    {
        return Point(this->coordinate - other.coordinate);
    }

    Point operator*(const Point &other) const
    {
        return Point(this->coordinate * other.coordinate);
    }

    Point operator/(const Point &other) const
    {
        return Point(this->coordinate / other.coordinate);
    }

    bool operator<(const Point &other) const
    {
        if (this->real() != other.real())
            return this->real() < other.real();
        return this->imag() < other.imag();
    }

    enum class CCWResult
    {
        COUNTER_CLOCKWISE = 2,
        CLOCKWISE = -2,
        ON_LINE_BACK = 1,
        ON_LINE_FRONT = -1,
        ON_SEGMENT = 0
    };

    static CCWResult ccw(const Point &a, Point b, Point c)
    {
        b.coordinate = b.coordinate - a.coordinate, c.coordinate = c.coordinate - a.coordinate;
        if (cross(b, c) > Point::EPS)
            return CCWResult::COUNTER_CLOCKWISE;
        if (cross(b, c) < -Point::EPS)
            return CCWResult::CLOCKWISE;
        if (dot(b, c) < 0)
            return CCWResult::ON_LINE_BACK;
        if (b.norm() < c.norm())
            return CCWResult::ON_LINE_FRONT;
        return CCWResult::ON_SEGMENT;
    }
};
