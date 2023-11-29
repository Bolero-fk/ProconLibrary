#include <bits/stdc++.h>
using namespace std;

/// @brief エラトステネスの篩による素数列挙
struct PrimesEnumerator
{
    using ll = long long;
    using P = pair<int, int>;
    int N;

    /// @brief primes:=N以下の素数
    vector<int> primes;

    /** @brief 入力された値以下の値が素数かどうかを判定できるクラス
     * @param N 素数かどうかを判定したい値の最大値
     * @note 計算量 O(NloglogN)
     */
    PrimesEnumerator(int N = 1) : N(N)
    {
        vector<bool> isChecked(N + 1);
        isChecked[0] = isChecked[1] = true;
        for (ll i = 2; i <= N; ++i)
        {
            if (isChecked[i])
                continue;
            primes.push_back(i);
            isChecked[i] = true;
            for (ll j = i * i; j <= N; j += i)
            {
                if (!isChecked[j])
                    isChecked[j] = i;
            }
        }
    }
};