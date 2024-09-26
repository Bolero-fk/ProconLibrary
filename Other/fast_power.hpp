#include <bits/stdc++.h>
using namespace std;

template <class S>
S fast_pow(S x, long long n, function<S(S, S)> mul, function<S()> e)
{
    S ans = e();

    while (n)
    {
        if (n & 1)
        {
            ans = mul(ans, x);
        }
        x = mul(x, x);
        n >>= 1;
    }

    return ans;
}
