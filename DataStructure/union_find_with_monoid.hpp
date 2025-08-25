#include <bits/stdc++.h>
#include <atcoder/dsu>
using namespace std;

class UnionFindWithMonoid : public atcoder::dsu
{
public:
    UnionFindWithMonoid(int N) : atcoder::dsu(N) {}

    int merge(int u, int v, function<void(int, int)> op)
    {
        if (this->same(u, v))
        {
            return this->leader(u);
        }

        u = this->leader(u), v = this->leader(v);

        int to = atcoder::dsu::merge(u, v);
        int from = u ^ v ^ to;
        op(from, to);

        return to;
    }
};