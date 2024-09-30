#include <bits/stdc++.h>
using namespace std;

#include "Other/fast_power.hpp"

template <typename T>
enable_if_t<is_integral_v<T> || is_same_v<T, __int128_t>, T>
mod_pow(T x, T n, T mod)
{
    assert(0 <= n);
    assert(0 < mod);
    assert(mod <= numeric_limits<T>::max() / mod);

    x %= mod;
    if (x < 0)
    {
        x += mod;
    }

    auto mul = [&](T a, T b) -> T
    {
        return (a * b) % mod;
    };

    auto e = [&]() -> T
    {
        return 1;
    };

    return fast_pow<T>(x, n, mul, e);
}