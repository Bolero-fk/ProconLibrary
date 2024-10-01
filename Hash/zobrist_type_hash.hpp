#include "Hash/zobrist_hash_base.hpp"

#include <bits/stdc++.h>
using namespace std;

class ZobristTypeHash : private ZobristHashBase
{
private:
    void build(const vector<long long> &v) override
    {
        hash_vector = vector<unsigned long long>(v.size() + 1, 0);

        set<long long> used;
        for (int i = 0; i < v.size(); i++)
        {
            if (used.contains(v[i]))
            {
                hash_vector[i + 1] = hash_vector[i];
                continue;
            }

            used.insert(v[i]);
            hash_vector[i + 1] = hash_vector[i] ^ ZobristHashBase::hash(v[i]);
        }
    }

public:
    unsigned long long get_range_hash(int l, int r) const override
    {
        assert(l == 0 && l < r && r < hash_vector.size());
        return hash_vector[r];
    }

    ZobristTypeHash(const vector<long long> &v)
    {
        build(v);
    };
};