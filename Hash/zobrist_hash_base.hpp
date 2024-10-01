#include <bits/stdc++.h>
using namespace std;

class ZobristHashBase
{
private:
    static unsigned long long splitmix64(uint64_t x)
    {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    static unsigned long long generate_random_value(unsigned long long x)
    {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }

protected:
    static unsigned long long hash(long long x)
    {
        static unordered_map<long long, unsigned long long> cache;
        if (cache.contains(x))
        {
            return cache[x];
        }

        cache[x] = generate_random_value(x);
        return cache[x];
    };

    virtual void build(const vector<long long> &v) = 0;
    ZobristHashBase() {};

public:
    vector<unsigned long long> hash_vector;
    virtual unsigned long long get_range_hash(int l, int r) const = 0;
    virtual ~ZobristHashBase() = default;
};
