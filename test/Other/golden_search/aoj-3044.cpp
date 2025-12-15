// competitive-verifier: PROBLEM https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=3044

#include "Other/golden_search.hpp"
#include <bits/stdc++.h>

using namespace std;

int main()
{
    long long N, M, S, G;
    cin >> N >> M >> S >> G;
    S--, G--;

    vector<vector<tuple<int, long long, long long>>> edges(N);
    for (int i = 0; i < M; i++)
    {
        long long U, V, A, B;
        cin >> U >> V >> A >> B;
        U--, V--;

        edges[U].push_back({V, A, B});
        edges[V].push_back({U, A, B});
    }

    vector<long long> dists(N, LONG_LONG_MAX);
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;

    dists[S] = 0;
    pq.push({0, S});

    while (pq.size())
    {
        auto [dist, now] = pq.top();
        pq.pop();

        if (dists[now] < dist)
        {
            continue;
        }

        for (auto [next, A, B] : edges[now])
        {
            auto f = [&](double t) -> double
            {
                return t + (double)B / (t + (double)A);
            };

            auto start = golden_search<true, double>(dist, 1e20, f).first;

            auto f_int = [&](long long t) -> long long
            {
                return t + (B + t + A - 1) / (t + A);
            };

            long long next_dist = min(f_int(floor(start)), f_int(ceil(start)));
            if (dists[next] <= next_dist)
            {
                continue;
            }

            dists[next] = next_dist;
            pq.push({next_dist, next});
        }
    }

    long long ans = dists[G];
    if (ans == LONG_LONG_MAX)
    {
        ans = -1;
    }
    cout << ans << endl;

    return 0;
};