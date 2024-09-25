#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)

/// @brief 約数列挙
/// @param n 約数を列挙したい数
/// @return nの約数(昇順)
vector<long long> enumerate_divisor(long long n)
{
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
    assert(true);
}