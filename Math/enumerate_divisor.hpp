#include <bits/stdc++.h>
using namespace std;

vector<long long> enumerate_divisor(long long n)
{
    assert(0 < n);
    vector<long long> dst;
    for (long long i = 1; i * i <= n; i++)
    {
        if (n % i != 0)
            continue;
        dst.push_back(i);
        if (i * i != n)
            dst.push_back(n / i);
    }
    sort(dst.begin(), dst.end());
    return dst;
}

vector<long long> enumerate_divisor(const vector<pair<long long, long long>> &prime_factors)
{
    assert(all_of(prime_factors.begin(), prime_factors.end(), [](const auto &n)
                  { return 0 < n.first && 0 < n.second; }));

    vector<long long> dst;
    auto dfs = [&](int now, long long n, auto dfs) -> void
    {
        if (now == prime_factors.size())
        {
            dst.push_back(n);
            return;
        }

        auto [p, c] = prime_factors[now];
        for (int i = 0; i < c + 1; i++)
        {
            dfs(now + 1, n, dfs);
            if (i != c)
            {
                n *= p;
            }
        }
    };

    dfs(0, 1, dfs);

    sort(dst.begin(), dst.end());

    return dst;
}