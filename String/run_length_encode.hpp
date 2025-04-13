#include <bits/stdc++.h>
using namespace std;

template <typename Container>
vector<pair<typename Container::value_type, int>> run_length_encode(const Container &v)
{
    using T = typename Container::value_type;
    vector<pair<T, int>> result;

    if (v.empty())
    {
        return result;
    }

    result = {{*v.begin(), 0}};

    for (const auto &n : v)
    {
        if (result.back().first != n)
        {
            result.push_back({n, 0});
        }

        result.back().second++;
    }

    return result;
}