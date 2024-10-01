#include "Hash/zobrist_hash_base.hpp"

#include <bits/stdc++.h>
using namespace std;

class ZobristParityHash : private ZobristHashBase
{
private:
    void build(const vector<long long> &v) override
    {
        hash_vector = vector<unsigned long long>(v.size() + 1, 0);
        for (int i = 0; i < v.size(); i++)
        {
            hash_vector[i + 1] = hash_vector[i] ^ ZobristHashBase::hash(v[i]);
        }
    }

public:
    unsigned long long get_range_hash(int l, int r) const override
    {
        assert(0 <= l && l < r && r < hash_vector.size());
        return hash_vector[r] ^ hash_vector[l];
    }

    ZobristParityHash(const vector<long long> &v)
    {
        build(v);
    };
};