// competitive-verifier: PROBLEM https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0304

#include "Math/difference_constraints_solver.hpp"
#include <bits/stdc++.h>

using namespace std;

int main()
{
    int N, C;
    cin >> N >> C;

    auto parse = [](string S) -> tuple<int, string, int, char, int>
    {
        int a = -1, b = -1, d = -1;
        string o;
        char s;

        int pre = 0;
        for (int i = 0; i < ssize(S); i++)
        {
            if (isdigit(S[i]))
            {
                continue;
            }

            if (a == -1)
            {
                a = stoi(string(S.begin() + pre, S.begin() + i));
                if (S[i] == '*')
                {
                    o = "*";
                    pre = i + 1;
                }
                else
                {
                    o = string(1, S[i]) + string(1, S[i + 1]);
                    i++;
                    pre = i + 1;
                }
            }
            else if (b == -1)
            {
                b = stoi(string(S.begin() + pre, S.begin() + i));
                s = S[i];
                pre = i + 1;
            }
        }
        d = stoi(string(S.begin() + pre, S.end()));

        return {a, o, b, s, d};
    };

    vector<array<int, 3>> abd;
    DifferenceConstraintsSolver<long long> solver(N);

    for (int i = 0; i < C; i++)
    {
        string S;
        cin >> S;
        auto [a, o, b, s, d] = parse(S);
        a--, b--;

        if (o == "<=")
        {
            swap(a, b);
        }

        if (o == "*")
        {
            if (s == '-')
            {
                solver.add_leq_constraint(a, b, d);
                solver.add_leq_constraint(b, a, d);
            }
            if (s == '+')
            {
                abd.push_back({a, b, d});
            }
        }
        else
        {
            // 0 <= a - b <= d
            if (s == '-')
            {
                solver.add_geq_constraint(a, b, 0);
                solver.add_leq_constraint(a, b, d);
            }

            // d <= a - b
            if (s == '+')
            {
                solver.add_geq_constraint(a, b, d);
            }
        }
    }

    long long ans = -1;
    // abd の制約については全通り確かめる。
    for (int bit = 0; bit < (1 << ssize(abd)); bit++)
    {
        DifferenceConstraintsSolver<long long> temp = solver;
        for (int i = 0; i < ssize(abd); i++)
        {
            auto [a, b, d] = abd[i];
            if ((bit >> i) & 1)
            {
                temp.add_geq_constraint(a, b, d);
            }
            else
            {
                temp.add_geq_constraint(b, a, d);
            }
        }

        auto result = temp.solve(0);
        if (!result.first)
        {
            continue;
        }

        if (*min_element(result.second.begin(), result.second.end()) < 0)
        {
            continue;
        }

        long long sub_ans = *max_element(result.second.begin(), result.second.end());
        ans = max(ans, sub_ans);
    }

    if (ans == solver.INF)
    {
        cout << "inf" << endl;
    }
    else
    {
        cout << ans << endl;
    }

    return 0;
}