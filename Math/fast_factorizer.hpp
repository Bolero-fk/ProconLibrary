#include <bits/stdc++.h>
using namespace std;

#include "Math/primality_test.hpp"

struct FastFactorizer
{
private:
    static unsigned long long abs_diff(unsigned long long a, unsigned long long b)
    {
        return (a > b) ? (a - b) : (b - a);
    }

    // pollards_rho法によりNの約数を返す
    static unsigned long long pollards_rho(unsigned long long N)
    {
        if (PrimalityTest::is_prime(N))
        {
            return N;
        }

        unsigned long long m = 1ll << (bit_width(N) / 8);

        // 100回試して見つからなかったら失敗
        for (unsigned long long c = 1; c < 100; c++)
        {
            auto f = [&](unsigned long long x) -> unsigned long long
            { return ((__uint128_t(x) * x) + c) % N; };

            unsigned long long x0 = c % (N + 1);
            unsigned long long y = x0, q = 1, g = 1, ys = 0, x = 0;

            for (int r = 1; g <= 1; r <<= 1)
            {
                x = y;
                for (int i = 0; i < r; i++)
                {
                    y = f(y);
                }

                unsigned long long k = 0;
                while (k < r && g <= 1)
                {
                    ys = y;
                    for (int i = 0; i < min(m, r - k); i++)
                    {
                        y = f(y);
                        q = __uint128_t(q) * abs_diff(x, y) % N;
                    }
                    g = gcd(q, N);
                    k += m;
                }
            }

            if (g == N)
            {
                while (g <= 1)
                {
                    ys = f(ys);
                    g = gcd(abs_diff(x, ys), N);
                }
            }

            if (g != N)
            {
                return g;
            }
        }

        assert(false && "fail to factorize by pollards rho algorithm");
    }

public:
    static vector<long long> factorize(long long N)
    {
        assert(0 < N);

        if (N == 1)
        {
            return {};
        }

        long long p = pollards_rho(N);
        if (p == N)
        {
            return {p};
        }

        vector<long long> left = factorize(p);
        vector<long long> right = factorize(N / p);
        vector<long long> result;
        merge(left.begin(), left.end(), right.begin(), right.end(), back_inserter(result));
        return result;
    }
};