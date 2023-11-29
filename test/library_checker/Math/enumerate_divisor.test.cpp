#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_3_D"

#include <Math/enumerate_divisor.hpp>
#include <bits/stdc++.h>

using namespace std;

int main()
{
    long long a, b, c;
    cin >> a >> b >> c;

    vector<long long> divisor = enumerate_divisor(c);

    long long ans = 0;

    for (long long n : divisor)
    {
        if (a <= n && n <= b)
            ans++;
    }

    cout << ans << endl;

    return 0;
}