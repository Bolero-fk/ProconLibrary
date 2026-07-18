#include <bits/stdc++.h>
using namespace std;

struct IntegerLine
{
    using Point = std::pair<__int128_t, __int128_t>;
    using Intersection = std::array<__int128_t, 3>;

    // A*x + B*y + C = 0
    __int128_t A, B, C;

    IntegerLine(__int128_t A, __int128_t B, __int128_t C) : A(A), B(B), C(C)
    {
        assert(A != 0 || B != 0);
        normalize();
    }

    // 異なる2点を通る直線
    static IntegerLine through(Point p, Point q)
    {
        const auto [px, py] = p;
        const auto [qx, qy] = q;

        assert(p != q);

        return IntegerLine(py - qy, qx - px, px * qy - qx * py);
    }

    // 異なる2点の垂直二等分線
    static IntegerLine perpendicular_bisector(Point p, Point q)
    {
        const auto [px, py] = p;
        const auto [qx, qy] = q;

        assert(p != q);

        return IntegerLine(2 * (qx - px), 2 * (qy - py), px * px + py * py - qx * qx - qy * qy);
    }

    // 点を直線方程式の左辺へ代入した値
    __int128_t eval(Point p) const
    {
        const auto [x, y] = p;
        return A * x + B * y + C;
    }

    // 点が直線上にあるか
    bool contains(Point p) const
    {
        return eval(p) == 0;
    }

    // 2点が直線の同じ側にあるか
    // どちらかが直線上にある場合は false
    bool same_side(Point p, Point q) const
    {
        const __int128_t pValue = eval(p);
        const __int128_t qValue = eval(q);

        return (pValue > 0 && qValue > 0) || (pValue < 0 && qValue < 0);
    }

    // 2点が直線の反対側にあるか
    // どちらかが直線上にある場合は false
    bool opposite_side(Point p, Point q) const
    {
        const __int128_t pValue = eval(p);
        const __int128_t qValue = eval(q);

        return (pValue > 0 && qValue < 0) || (pValue < 0 && qValue > 0);
    }

    // 2直線が平行か
    bool is_parallel(const IntegerLine &other) const
    {
        return A * other.B == B * other.A;
    }

    // 2直線が同一か
    bool is_same(const IntegerLine &other) const
    {
        return A == other.A && B == other.B && C == other.C;
    }

    // 2直線が垂直か
    bool is_perpendicular(const IntegerLine &other) const
    {
        return A * other.A + B * other.B == 0;
    }

    // 交点を {xの分子, yの分子, 共通分母} で返す
    // 平行または同一直線の場合は std::nullopt
    std::optional<Intersection> intersection(const IntegerLine &other) const
    {
        __int128_t denominator = A * other.B - other.A * B;

        if (denominator == 0)
        {
            return std::nullopt;
        }

        __int128_t xNumerator = B * other.C - other.B * C;

        __int128_t yNumerator = C * other.A - other.C * A;

        if (denominator < 0)
        {
            denominator = -denominator;
            xNumerator = -xNumerator;
            yNumerator = -yNumerator;
        }

        return Intersection{xNumerator, yNumerator, denominator};
    }

private:
    static __int128_t abs_value(__int128_t value)
    {
        return value < 0 ? -value : value;
    }

    static __int128_t gcd(__int128_t a, __int128_t b)
    {
        a = abs_value(a);
        b = abs_value(b);

        while (b != 0)
        {
            const __int128_t remainder = a % b;
            a = b;
            b = remainder;
        }

        return a;
    }

    void normalize()
    {
        const __int128_t divisor = gcd(gcd(A, B), C);

        A /= divisor;
        B /= divisor;
        C /= divisor;

        // 最初の非ゼロ係数を正に統一する。
        // A と B が同時に 0 になることはない。
        if (A < 0 || (A == 0 && B < 0))
        {
            A = -A;
            B = -B;
            C = -C;
        }
    }
};
