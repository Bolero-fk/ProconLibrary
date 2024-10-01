#include "Hash/zobrist_hash_base.hpp"
#include "Math/prime_factorize.hpp"

#include <bits/stdc++.h>
using namespace std;

class ZobristCubicHash : private ZobristHashBase
{
private:
    void build(const vector<long long> &v) override
    {
        hash_vector = vector<unsigned long long>(v.size() + 1, 0);

        unordered_map<long long, long long> prime_counts;
        for (int i = 0; i < v.size(); i++)
        {
            hash_vector[i + 1] = hash_vector[i];
            for (auto [p, cnt] : prime_factorize(v[i]))
            {
                cnt %= 3;
                for (int j = 0; j < cnt; j++)
                {
                    prime_counts[p]++;
                    if (prime_counts[p] % 3 == 0)
                    {
                        hash_vector[i + 1] ^= ZobristHashBase::hash(p);
                    }
                    if (prime_counts[p] % 3 == 1)
                    {
                        hash_vector[i + 1] ^= ZobristHashBase::hash(p * p);
                    }
                    if (prime_counts[p] % 3 == 2)
                    {
                        hash_vector[i + 1] ^= ZobristHashBase::hash(p) ^ ZobristHashBase::hash(p * p);
                    }
                }
            }
        }
    }

public:
    unsigned long long get_range_hash(int l, int r) const override
    {
        assert(0 <= l && l < r && r < hash_vector.size());
        return hash_vector[r] ^ hash_vector[l];
    }

    ZobristCubicHash(const vector<long long> &v)
    {
        build(v);
    };
};