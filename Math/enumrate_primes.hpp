#include <bits/stdc++.h>
using namespace std;

/// @brief エラトステネスの篩による素数列挙
struct PrimesEnumerator
{
    using ll = long long;
    using P = pair<int, int>;
    int n;

    /// @brief f[i]:=i持つ最小の素因数
    vector<int> f;

    /// @brief primes:=素数
    vector<int> primes;

    /** @brief 入力された値以下の値が素数かどうかを判定できるクラス
     * @param N 素数かどうかを判定したい値の最大値
     * @note 計算量 O(NloglogN)
     */
    PrimesEnumerator(int N = 1) : n(N), f(N + 1)
    {
        f[0] = f[1] = -1;
        for (ll i = 2; i <= N; ++i)
        {
            if (f[i])
                continue;
            primes.push_back(i);
            f[i] = i;
            for (ll j = i * i; j <= N; j += i)
            {
                if (!f[j])
                    f[j] = i;
            }
        }
    }

    /** @brief 引数が素数かどうかを判定します
     * @param x 素数かどうかを判定したい値
     * @return 引数が素数かどうかの判定結果
     * @details 入力 3 → 出力 ture, 入力 4 → 出力 false
     */
    bool isPrime(int x) { return f[x] == x; }

    /** @brief xを素因数分解した結果を一次元配列で返します
     * @param x 素因数分解したい値
     * @return 素因数分解の結果
     * @details 入力 12 → 出力 2 2 3, 入力 4 → 出力 2 2
     */
    vector<int> factorList(int x)
    {
        vector<int> res;
        while (x != 1)
        {
            res.push_back(f[x]);
            x /= f[x];
        }
        return res;
    }

    /** @brief xを素因数分解した結果をpairの配列で返します
     * @param x 素因数分解したい値
     * @return 素因数分解の結果
     * @details 入力 12 → 出力 [{2, 2}, {3, 1}], 入力 4 → 出力 [{2, 2}]
     */
    vector<P> factor(int x)
    {
        vector<int> fl = factorList(x);
        if (fl.size() == 0)
            return {};
        vector<P> res(1, P(fl[0], 0));
        for (int p : fl)
        {
            if (res.back().first == p)
            {
                res.back().second++;
            }
            else
            {
                res.emplace_back(p, 1);
            }
        }
        return res;
    }

    /** @brief xを素因数分解した結果をpairの配列で返します
     * @param x 素因数分解したい値
     * @return 素因数分解の結果
     * @details 入力 12 → 出力 [{2, 2}, {3, 1}], 入力 4 → 出力 [{2, 2}]
     * @note 入力値が非常に大きいが素因数がエラトステネスの篩の値以下のときに使用する
     */
    vector<pair<ll, int>> factor(ll x)
    {
        vector<pair<ll, int>> res;
        for (int p : primes)
        {
            int y = 0;
            while (x % p == 0)
                x /= p, ++y;
            if (y != 0)
                res.emplace_back(p, y);
        }
        if (x != 1)
            res.emplace_back(x, 1);
        return res;
    }
};