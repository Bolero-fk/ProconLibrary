#include <bits/stdc++.h>
using namespace std;

#include "Other/binary_search.hpp"

template <typename T>
enable_if_t<is_integral_v<T>, T>
kth_root(T a, T k)
{
    assert(0 <= a);
    assert(0 < k);

    if (a == 1)
    {
        return 1;
    }
    if (k == 1)
    {
        return a;
    }

    auto check_root = [&](T x) -> bool
    {
        T tmp = 1;
        for (T i = 0; i < k; i++)
        {
            if (tmp > a / x)
            {
                return false;
            }

            tmp *= x;
        }

        return tmp <= a;
    };

    return bin_search<T>(0, a, check_root);
}