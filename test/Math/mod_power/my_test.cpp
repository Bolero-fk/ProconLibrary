// competitive-verifier: STANDALONE

#include "Math/mod_power.hpp"
#include <bits/stdc++.h>

using namespace std;

int greedy_solve(int x, int n, int mod)
{
    int ans = 1;
    for (int i = 0; i < n; i++)
    {
        ans *= x;
    }

    while (ans < 0)
    {
        ans += mod;
    }

    return ans % mod;
}

int solve(int x, int n, int mod)
{
    return mod_pow<long long>(x, n, mod);
}

int main()
{
    for (int x = -10; x <= 0; x++)
    {
        for (int n = 0; n <= 5; n++)
        {
            assert(solve(x, n, 1000000) == greedy_solve(x, n, 1000000));
        }
    }

    return 0;
}