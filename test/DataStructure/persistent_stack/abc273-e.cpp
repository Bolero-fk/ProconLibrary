// competitive-verifier: PROBLEM https://atcoder.jp/contests/abc273/tasks/abc273_e

#include "DataStructure/persistent_stack.hpp"
#include <bits/stdc++.h>

using namespace std;

int main()
{

    long long Q;
    cin >> Q;

    PersistentStack<int> stack;
    unordered_map<int, PersistentStack<int>> notebook;

    for (int q = 0; q < Q; q++)
    {
        string T;
        cin >> T;
        if (T == "ADD")
        {
            int x;
            cin >> x;
            stack.push(x);
        }
        if (T == "DELETE")
        {
            if (!stack.empty())
            {
                stack.pop();
            }
        }
        if (T == "SAVE")
        {
            int y;
            cin >> y;
            notebook[y] = stack;
        }
        if (T == "LOAD")
        {
            int z;
            cin >> z;
            stack = notebook[z];
        }

        if (!stack.empty())
        {
            cout << stack.top();
        }
        else
        {
            cout << -1;
        }

        cout << " \n"[q == Q - 1];
    }

    return 0;
}