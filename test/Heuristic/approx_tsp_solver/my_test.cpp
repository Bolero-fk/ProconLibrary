// competitive-verifier: STANDALONE

#include "Heuristic/approx_tsp_solver.hpp"
#include <bits/stdc++.h>

using namespace std;

long double solve(const int N, const vector<long double> &X, const vector<long double> &Y)
{
    vector<vector<long double>> costs(N, vector<long double>(N, 0));
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            costs[i][j] = sqrtl(powl(X[i] - X[j], 2) + powl(Y[i] - Y[j], 2));
        }
    }

    vector<int> root(N);
    for (int i = 0; i < N; i++)
    {
        root[i] = i;
    }
    ApproxTspSolver<long double> tsp_solver;
    auto ans = tsp_solver.solve(root, costs);
    return ans.first;
}

void solve1()
{
    const int N = 4;
    const vector<long double> X = {0, 0, 1, 1}, Y = {0, 1, 0, 1};
    const long double my_ans = solve(N, X, Y);
    const long double true_ans = 4.000000000000;

    assert(abs(my_ans - true_ans) < 0.001);
}

void solve2()
{
    const int N = 7;
    const vector<long double> X = {2, 2, 4, 1, 7, 5, 6}, Y = {5, 3, 1, 1, 2, 3, 5};
    const long double my_ans = solve(N, X, Y);
    const long double true_ans = 18.870481592668;

    assert(abs(my_ans - true_ans) < 0.001);
}

void solve3()
{
    const int N = 11;
    const vector<long double> X = {642, 16, 898, 264, 751, 92, 963, 152, 333, 632, 27};
    const vector<long double> Y = {364, 717, 53, 824, 558, 496, 277, 618, 743, 559, 40};
    const long double my_ans = solve(N, X, Y);
    const long double true_ans = 3270.811560094203;

    assert(abs(my_ans - true_ans) < 0.001);
}

void solve4()
{
    const int N = 15;
    const vector<long double> X = {776, 218, 839, 975, 192, 90, 493, 285, 441, 445, 560, 784, 570, 982, 452};
    const vector<long double> Y = {273, 998, 577, 670, 465, 329, 586, 494, 175, 612, 777, 266, 778, 130, 599};
    const long double my_ans = solve(N, X, Y);
    const long double true_ans = 3441.451976970622;

    assert(abs(my_ans - true_ans) < 0.001);
}

int main()
{

    solve1();
    solve2();
    solve3();
    solve4();

    return 0;
}