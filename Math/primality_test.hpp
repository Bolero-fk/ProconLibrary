#include <bits/stdc++.h>
using namespace std;

#include "Math/mod_power.hpp"

struct PrimalityTest
{
private:
    static bool miller_rabin(long long N, const vector<long long> &A)
    {
        const int s = countr_zero((unsigned long long)N - 1);
        const long long d = (N - 1) >> s;

        auto is_composite = [&](long long a) -> bool
        {
            // Fermat の小定理が成り立たない
            if (a % N == 0)
            {
                return false;
            }

            long long x = mod_pow<__int128_t>(a, d, N);
            if (x == 1 || x == N - 1)
            {
                return false;
            }

            for (int t = 0; t < s - 1; ++t)
            {
                x = __int128_t(x) * x % N;
                if (x == N - 1)
                {
                    return false;
                }
            }

            return true;
        };

        return none_of(A.begin(), A.end(), is_composite);
    }

public:
    static bool is_prime(long long N)
    {
        assert(0 <= N);
        if (N <= 2)
        {
            return N == 2;
        }
        if (N % 2 == 0)
        {
            return false;
        }

        return miller_rabin(N, {2, 325, 9375, 28178, 450775, 9780504, 1795265022});
    }
};