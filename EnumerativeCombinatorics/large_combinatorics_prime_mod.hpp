#include <bits/stdc++.h>

// n が非常に大きく、r が比較的小さい(r <= 10^7程度)場合に使う組合せライブラリ。
// P(n, r), C(n, r), H(n, r) を O(r) で計算する。
// n が前計算可能な大きさで、大量に問い合わせる場合は combinatorics を使う。
template <class mint>
class large_combinatorics
{
private:
    std::vector<mint> inv;
    std::vector<mint> fact_inv;

    void expand(long long r)
    {
        assert(0 <= r);

        // C(n, r), H(n, r) では r! の逆元を使うため、
        // r >= mod ではこのライブラリは使えない。
        // その場合は Lucas の定理など別手法が必要。
        assert(r < mint::mod());

        int old_size = (int)fact_inv.size();
        if (r < old_size)
        {
            return;
        }

        int new_size = (int)r + 1;

        inv.resize(new_size);
        fact_inv.resize(new_size);

        if (old_size == 0)
        {
            inv[0] = 0;
            fact_inv[0] = 1;
            old_size = 1;
        }

        if (old_size == 1 && new_size >= 2)
        {
            inv[1] = 1;
            fact_inv[1] = 1;
            old_size = 2;
        }

        for (int i = old_size; i < new_size; i++)
        {
            inv[i] = -mint(mint::mod() / i) * inv[mint::mod() % i];
            fact_inv[i] = fact_inv[i - 1] * inv[i];
        }
    }

public:
    large_combinatorics() = default;

    mint P(long long n, long long r)
    {
        if (n < 0 || r < 0)
        {
            return 0;
        }

        if (n < r)
        {
            return 0;
        }

        mint ans = 1;
        for (long long i = 0; i < r; i++)
        {
            ans *= n - i;
        }

        return ans;
    }

    mint C(long long n, long long r)
    {
        if (n < 0 || r < 0)
        {
            return 0;
        }

        if (n < r)
        {
            return 0;
        }

        expand(r);

        return P(n, r) * fact_inv[r];
    }

    mint H(long long n, long long r)
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