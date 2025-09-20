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
    // 大きすぎるとcheck(x)のxが不当に大きくなるのでよき大きさに切る。
    assert(abs(ok) < 1e20 && abs(ng) < 1e20);

    for (int i = 0; i < 100; i++)
    {
        T mid = midpoint(ok, ng);
        (check(mid) ? ok : ng) = mid;
    }
    return ok;
}
