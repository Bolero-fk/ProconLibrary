#include <bits/stdc++.h>
using namespace std;

// フィボナッチ数列による三分探索。「狭義」凸関数の極値を探索する。返り値は{x, f(x)}
template <bool Minimize, typename T>
pair<double, T> golden_search(double x_low, double x_high, function<T(double)> f)
{
    assert(x_low <= x_high);

    auto comp = [](T a, T b) -> bool
    {
        return Minimize ? a <= b : a >= b;
    };

    const double PHI = 1.61803398874989484;     // (1 + √5) / 2
    const double DIVPHI = 0.381966011250105151; // 1 / (1 + PHI);

    double x_mid_low = (x_low * PHI + x_high) * DIVPHI;
    double x_mid_high = (x_low + x_high * PHI) * DIVPHI;

    double f_low = f(x_low), f_mid_low = f(x_mid_low), f_mid_high = f(x_mid_high), f_high = f(x_high);

    for (int iter = 0; iter < 100; iter++)
    {
        if (comp(f_mid_low, f_mid_high))
        {
            tie(x_mid_low, x_mid_high, x_high) = tuple<double, double, double>{(x_low * PHI + x_mid_high) * DIVPHI, x_mid_low, x_mid_high};
            tie(f_mid_low, f_mid_high, f_high) = tuple<double, double, double>{f(x_mid_low), f_mid_low, f_mid_high};
        }
        else
        {
            tie(x_low, x_mid_low, x_mid_high) = tuple<double, double, double>{x_mid_low, x_mid_high, (x_mid_low + x_high * PHI) * DIVPHI};
            tie(f_low, f_mid_low, f_mid_high) = tuple<double, double, double>{f_mid_low, f_mid_high, f(x_mid_high)};
        }
    }

    return {x_low, f_low};
}