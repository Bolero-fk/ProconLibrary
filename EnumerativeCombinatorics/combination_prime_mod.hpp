#include <bits/stdc++.h>
using namespace std;

template <class mint>
class combinatorics
{
private:
    int max_n;
    vector<mint> fact, ifact;

public:
    combinatorics(int n) : max_n(n), fact(n + 1), ifact(n + 1)
    {
        assert(n < mint::mod());

        fact[0] = 1;
        for (int i = 1; i <= n; ++i)
            fact[i] = fact[i - 1] * i;

        ifact[n] = fact[n].inv();
        for (int i = n; i >= 1; --i)
            ifact[i - 1] = ifact[i] * i;
    }

    mint operator()(int n, int k)
    {
        return C(n, k);
    }

    // nCr
    mint C(int n, int r)
    {
        if (n < 0 || r < 0 || r > n)
            return 0;
        assert(n <= max_n);

        return fact[n] * ifact[r] * ifact[n - r];
    }

    // nPr
    mint P(int n, int r)
    {
        if (n < 0 || r < 0 || r > n)
            return 0;
        assert(n <= max_n);

        return fact[n] * ifact[n - r];
    }

    // nHr
    mint H(int n, int r)
    {
        if (n < 0 || r < 0)
            return 0;

        if (n == 0)
            return r == 0 ? 1 : 0;

        return C(n + r - 1, r);
    }
};