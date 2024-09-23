// competitive-verifier: PROBLEM https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=NTL_1_A

#include <Math/prime_factorize.hpp>
#include <bits/stdc++.h>

using namespace std;

int main()
{
    long long n;
    cin >> n;

    vector<pair<long long, long long>> factors = prime_factorize(n);

    string ans = to_string(n) + ": ";
    for (auto [factor, count] : factors)
    {
        for (int i = 0; i < count; i++)
        {
            ans += to_string(factor) + " ";
        }
    }
    ans.pop_back();
    cout << ans << endl;

    return 0;
}