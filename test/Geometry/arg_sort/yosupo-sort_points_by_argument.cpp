// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/sort_points_by_argument

#include "Geometry/arg_sort.hpp"
#include <bits/stdc++.h>

using namespace std;

int main()
{
    int N;
    cin >> N;

    vector<pair<long long, long long>> XY(N);

    for (int i = 0; i < N; i++)
    {
        cin >> XY[i].first >> XY[i].second;
    }

    sort(XY.begin(), XY.end(), arg_comp);

    for (int i = 0; i < N; i++)
    {
        cout << XY[i].first << " " << XY[i].second << endl;
    }

    return 0;
}