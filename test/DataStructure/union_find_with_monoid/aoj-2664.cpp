// competitive-verifier: PROBLEM https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2664

#include "DataStructure/union_find_with_monoid.hpp"
#include <bits/stdc++.h>

using namespace std;

int main()
{
    int N;
    cin >> N;

    unordered_map<string, int> mp;
    vector<int> x(N);
    for (int i = 0; i < N; i++)
    {
        string a;
        cin >> a >> x[i];
        mp[a] = mp.size();
    }

    int M;
    cin >> M;

    auto op = [&](int from, int to)
    {
        x[to] = min(x[from], x[to]);
    };

    UnionFindWithMonoid uf(N);
    for (int i = 0; i < M; i++)
    {
        string s, t;
        cin >> s >> t;
        uf.merge(mp[s], mp[t], op);
    }

    int ans = 0;
    for (auto group : uf.groups())
    {
        ans += group.size() * x[uf.leader(group.front())];
    }
    cout << ans << endl;

    return 0;
}