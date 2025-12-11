#include <bits/stdc++.h>
using namespace std;

// フィボナッチ数列による三分探索。「狭義」凸関数の極値を探索する。返り値は{x, f(x)}
template <bool Minimize, typename T>
pair<long long, T> fibonacci_search(long long x_low, long long x_high, function<T(long long)> f)
{
    assert(x_low <= x_high);
    long long offset = x_low - 1;

    T INF = Minimize ? numeric_limits<T>::max() : numeric_limits<T>::lowest();
    auto comp = [](T a, T b) -> bool
    {
        return Minimize ? a >= b : a <= b;
    };

    vector<long long> fib = {1, 1};
    while (fib.back() <= x_high - offset)
    {
        fib.push_back(fib[fib.size() - 1] + fib[fib.size() - 2]);
    }

    unordered_map<long long, T> fx_cache;
    auto eval = [&](long long idx) -> T
    {
        long long x = idx + offset;
        if (x_low <= x && x <= x_high)
        {
            if (!fx_cache.contains(x))
            {
                fx_cache[x] = f(x);
            }
            return fx_cache[x];
        }

        return INF;
    };

    long long l_idx = 0, r_idx = fib.back();
    while (2 <= fib.size())
    {
        long long step_len = fib[fib.size() - 2];

        long long mid_l_idx = r_idx - step_len, mid_r_idx = l_idx + step_len;

        T fl = eval(mid_l_idx), fr = eval(mid_r_idx);

        if (comp(fl, fr))
        {
            l_idx = mid_l_idx;
        }
        else
        {
            r_idx = mid_r_idx;
        }

        fib.pop_back();
    }

    return {l_idx + offset, eval(l_idx)};
}