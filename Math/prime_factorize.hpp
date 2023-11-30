#include <bits/stdc++.h>
using namespace std;

/// @brief 素因数分解
/// @param N 素因数分解をしたい数
/// @return vector<i, j>の時iのj乗を因数に持つ
vector<pair<long long, long long>> prime_factorize(long long N)
{
    long long tempN = N;
    vector<pair<long long, long long>> dst;
    for (long long i = 2; i * i <= tempN; i++)
    {
        if (N % i == 0)
        {
            dst.push_back(make_pair(i, 0));
            while (N % i == 0)
            {
                dst.back().second++;
                N /= i;
            }
        }
    }
    if (N != 1)
        dst.push_back(make_pair(N, 1));
    return dst;
}