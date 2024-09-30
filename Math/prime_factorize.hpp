#include <bits/stdc++.h>
using namespace std;

vector<pair<long long, long long>> prime_factorize(long long N)
{
    assert(0 < N);

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