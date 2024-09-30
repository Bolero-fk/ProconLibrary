#include <bits/stdc++.h>
using namespace std;

vector<long long> enumerate_primes(long long n)
{
    assert(0 < n);

    vector<long long> primes;
    vector<bool> isChecked(n + 1, false);
    isChecked[0] = isChecked[1] = true;
    for (long long i = 2; i <= n; i++)
    {
        if (isChecked[i])
        {
            continue;
        }

        primes.push_back(i);
        isChecked[i] = true;

        for (long long j = i * i; j <= n; j += i)
        {
            if (!isChecked[j])
            {
                isChecked[j] = true;
            }
        }
    }

    return primes;
}