#include <bits/stdc++.h>
using namespace std;

template <typename T>
enable_if_t<is_integral_v<T>, T>
bin_search(T ok, T ng, function<bool(T)> check)
{
    while (max(ok, ng) - min(ok, ng) > 1)
    {
        T mid = midpoint(ok, ng);
        (check(mid) ? ok : ng) = mid;
    }
    return ok;
}

template <typename T>
enable_if_t<is_floating_point_v<T>, T>
bin_search(T ok, T ng, function<bool(T)> check)
{
    while (true)
    {
        T mid = midpoint(ok, ng);
        if (ok == mid || ng == mid)
        {
            break;
        }
        (check(mid) ? ok : ng) = mid;
    }

    return ok;
}