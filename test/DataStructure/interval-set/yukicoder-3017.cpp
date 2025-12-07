// competitive-verifier: PROBLEM https://yukicoder.me/problems/no/3017

#include "DataStructure/interval_set.hpp"
#include <bits/stdc++.h>

using namespace std;

int main()
{
    int N;
    cin >> N;

    IntervalSet<int> interval_set;

    for (int i = 0; i < N; i++)
    {
        int H;
        cin >> H;
        if (i % 2 == 0)
        {
            interval_set.add_interval(0, H);
        }
        else
        {
            interval_set.erase_interval(0, H);
        }
        cout << interval_set.get_sum_lentgth() << endl;
    }

    return 0;
}