// competitive-verifier: PROBLEM https://yukicoder.me/problems/no/198

#include "Other/fibonacci_search.hpp"
#include <bits/stdc++.h>

using namespace std;

int main()
{
    long long B, N;
    cin >> B >> N;
    vector<long long> C(N);
    for (int i = 0; i < N; i++)
    {
        cin >> C[i];
        B += C[i];
    }

    auto f = [&](long long x) -> long long
    {
        long long sum = 0;
        for (int i = 0; i < N; i++)
        {
            sum += abs(C[i] - x);
        }

        return sum;
    };

    auto [x, fx] = fibonacci_search<true, long long>(0, B / N, f);
    cout << fx << endl;

    return 0;
};