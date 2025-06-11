// competitive-verifier: PROBLEM https://yukicoder.me/problems/no/2909
// competitive-verifier: ERROR 1e-5

#include "DataStructure/kd_tree.hpp"
#include <bits/stdc++.h>

using namespace std;

int main()
{
    int N, M, K;
    cin >> N >> M >> K;

    long double P, Q;
    cin >> P >> Q;

    vector<array<long double, 2>> stations(N);
    for (int i = 0; i < N; i++)
    {
        cin >> stations[i][0] >> stations[i][1];
    }

    vector<array<long double, 2>> targets(K);
    for (int i = 0; i < K; i++)
    {
        cin >> targets[i][0] >> targets[i][1];
    }

    long double V;
    cin >> V;

    vector<array<int, 2>> ST(M);
    for (int i = 0; i < M; i++)
    {
        cin >> ST[i][0] >> ST[i][1];
        ST[i][0]--, ST[i][1]--;
    }

    KDTree<long double, 2> kd_tree(stations);

    long double ans = 0;
    for (auto target : targets)
    {
        // 直接目的地に行く
        long double dist1 = hypotl(P - target[0], Q - target[1]);

        // 駅を使って移動する
        long double sub_dis1;
        auto point1 = kd_tree.nearest({P, Q}).value();
        long double sub_dist1 = hypotl(P - point1.point[0], Q - point1.point[1]);

        auto point2 = kd_tree.nearest(target).value();
        long double sub_dist2 = hypotl(target[0] - point2.point[0], target[1] - point2.point[1]);

        long double dist2 = sub_dist1 + sub_dist2;

        ans += min(dist1, dist2) * 2;
    }

    cout << fixed << setprecision(15) << ans << endl;

    return 0;
}