#include <bits/stdc++.h>
using namespace std;

vector<long long> enumerate_divisor(long long n)
{
    assert(0 < n);
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
}