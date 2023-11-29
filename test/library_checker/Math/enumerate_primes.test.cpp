#define PROBLEM "https://judge.yosupo.jp/problem/enumerate_primes"

#include <Math/enumerate_primes.hpp>
#include <bits/stdc++.h>

using namespace std;

int main()
{
    long long N, A, B;

    cin >> N >> A >> B;

    PrimesEnumerator primesEnumerator(N);

    long long piN = primesEnumerator.primes.size();

    vector<long long> ps;
    for (int i = B; i < piN; i += A)
    {
        ps.push_back(primesEnumerator.primes[i]);
    }

    long long X = ps.size();

    cout << piN << " " << X << endl;

    for (long long p : ps)
    {
        cout << p << " ";
    }
    cout << endl;

    return 0;
}