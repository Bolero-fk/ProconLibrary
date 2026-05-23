#include <bits/stdc++.h>

// n が比較的小さく(n <= 10^7程度)、n < mod を満たす場合に使う組合せライブラリ。
// n まで階乗と階乗逆元を前計算し、P(n, r), C(n, r), H(n, r) を O(1) で計算する。
// n が非常に大きく、r が小さい場合は large_combinatorics を使う。
template <class mint>
class combinatorics
{
private:
    std::vector<mint> fact;
    std::vector<mint> inv;
    std::vector<mint> fact_inv;

    void expand(int n)
    {
        assert(0 <= n);

        // fact[n] を使うため、n >= mod ではこのライブラリは使えない。
        // n が大きい場合は large_combinatorics を使う。
        assert(n < mint::mod());

        int old_size = (int)fact.size();
        if (n < old_size)
        {
            return;
        }

        int new_size = n + 1;

        fact.resize(new_size);
        inv.resize(new_size);
        fact_inv.resize(new_size);

        if (old_size == 0)
        {
            fact[0] = 1;
            fact_inv[0] = 1;
            old_size = 1;
        }

        if (old_size == 1 && new_size >= 2)
        {
            fact[1] = 1;
            inv[1] = 1;
            fact_inv[1] = 1;
            old_size = 2;
        }

        for (int i = old_size; i < new_size; i++)
        {
            fact[i] = fact[i - 1] * i;
            inv[i] = -mint(mint::mod() / i) * inv[mint::mod() % i];
            fact_inv[i] = fact_inv[i - 1] * inv[i];
        }
    }

public:
    combinatorics() = default;

    combinatorics(int n)
    {
        expand(n);
    }

    mint operator()(int n, int r)
    {
        return C(n, r);
    }

    mint P(int n, int r)
    {
        if (n < 0 || r < 0)
        {
            return 0;
        }

        if (n < r)
        {
            return 0;
        }

        expand(n);

        return fact[n] * fact_inv[n - r];
    }

    mint C(int n, int r)
    {
        if (n < 0 || r < 0)
        {
            return 0;
        }

        if (n < r)
        {
            return 0;
        }

        expand(n);

        return fact[n] * fact_inv[r] * fact_inv[n - r];
    }

    mint H(int n, int r)
    {
        if (n < 0 || r < 0)
        {
            return 0;
        }

        if (n == 0)
        {
            return r == 0 ? mint(1) : mint(0);
        }

        return C(n + r - 1, r);
    }
};