#include <bits/stdc++.h>
using namespace std;

class ZobristHash
{
    // https://drken1215.hatenablog.com/entry/2022/05/12/105000
    static unsigned long long splitmix64(uint64_t x)
    {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    static unsigned long long rand(unsigned long long x)
    {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }

    static unsigned long long hash(long long x)
    {
        static unordered_map<long long, unsigned long long> cache;
        if (cache.contains(x))
        {
            return cache[x];
        }

        cache[x] = rand(x);
        return cache[x];
    };

    void build_parity_hash(vector<long long> v)
    {
        hash_vector = {0};
        for (auto n : v)
        {
            hash_vector.push_back(hash_vector.back() ^ hash(n));
        }
    }

    unsigned long long get_parity_hash(int l, int r)
    {
        return hash_vector[r] ^ hash_vector[l];
    }

    void build_type_hash(vector<long long> v)
    {
        hash_vector = {0};
        set<long long> used;

        for (auto n : v)
        {
            if (used.contains(n))
            {
                hash_vector.push_back(hash_vector.back());
                continue;
            }

            used.insert(n);
            hash_vector.push_back(hash_vector.back() ^ hash(n));
        }
    }

    unsigned long long get_type_hash(int l, int r)
    {
        assert(l == 0);
        return hash_vector[r];
    }

    void build_count_hash(vector<long long> v)
    {
        hash_vector = {0};
        for (auto n : v)
        {
            hash_vector.push_back(hash_vector.back() + hash(n));
        }
    }

    unsigned long long get_count_hash(int l, int r)
    {
        return hash_vector[r] - hash_vector[l];
    }

public:
    enum HASH_TYPE
    {
        PARITY, // 集合内の数値の偶奇
        TYPE,   // 集合内の数値の種類(0からの累積ハッシュのみ計算可能)
        COUNT,  // 集合内の数値の個数
    };

    vector<unsigned long long> hash_vector;
    function<unsigned long long(int, int)> get_accumulate_hash;

    ZobristHash(vector<long long> v, HASH_TYPE hash_type)
    {
        if (hash_type == HASH_TYPE::PARITY)
        {
            build_parity_hash(v);
            get_accumulate_hash = [this](int l, int r)
            { return get_parity_hash(l, r); };
        }
        else if (hash_type == HASH_TYPE::TYPE)
        {
            build_type_hash(v);
            get_accumulate_hash = [this](int l, int r)
            { return get_type_hash(l, r); };
        }
        else if (hash_type == HASH_TYPE::COUNT)
        {
            build_count_hash(v);
            get_accumulate_hash = [this](int l, int r)
            { return get_count_hash(l, r); };
        }
        else
        {
            assert(false);
        }
    };

    static unsigned long long get_hash(long long x)
    {
        return hash(x);
    }
};