#include <bits/stdc++.h>
using namespace std;

class FastRandomEngine
{
private:
    // 0以上UINT_MAX(0xffffffff)以下の整数をとる乱数 xorshift https://ja.wikipedia.org/wiki/Xorshift
    static uint32_t randXor()
    {
        static uint32_t x = 123456789;
        static uint32_t y = 362436069;
        static uint32_t z = 521288629;
        static uint32_t w = 88675123;
        uint32_t t;

        t = x ^ (x << 11);
        x = y;
        y = z;
        z = w;
        return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
    }

    // 0以上1未満の小数をとる乱数
    static double rand01()
    {
        return (randXor() + 0.5) * (1.0 / UINT_MAX);
    }

public:
    using result_type = uint32_t;

    FastRandomEngine(uint32_t seed = 0) : state(seed) {}

    uint32_t operator()()
    {
        return randXor();
    }

    static constexpr uint32_t min()
    {
        return std::numeric_limits<uint32_t>::min();
    }

    static constexpr uint32_t max()
    {
        return std::numeric_limits<uint32_t>::max();
    }

    static long long random_int(pair<long long, long long> min_max)
    {
        return random_int(min_max.first, min_max.second);
    }

    static long long random_int(long long min, long long max)
    {
        long long width = max - min + 1;

        return randXor() % width + min;
    }

    static long double random_real(pair<long double, long double> min_max)
    {
        return random_real(min_max.first, min_max.second);
    }

    static long double random_real(long double min, long double max)
    {
        long double width = max - min;

        return rand01() * width + min;
    }

private:
    uint32_t state;
};
FastRandomEngine rand_engine(0);

template <class T>
static void shuffle_vector(vector<T> &v)
{
    shuffle(v.begin(), v.end(), rand_engine);
}