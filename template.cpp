#include <bits/stdc++.h>

using namespace std;
#define rep(i, n) for (long long i = 0; i < (long long)(n); i++)
#define FOR(i, s, e) for (long long i = (long long)(s); i <= (long long)(e); i++)
#define printYesNo(is_ok) puts(is_ok ? "Yes" : "No");
#define SORT(v) sort(v.begin(), v.end())
#define RSORT(v) sort(v.rbegin(), v.rend())
#define REVERSE(v) reverse(v.begin(), v.end())

template <typename T>
void printlnVector(const T &v)
{
    for (auto n : v)
    {
        cout << n << endl;
    }
}

template <typename T>
void printVector(const T &v, char suffix = '\n')
{
    for (auto n : v)
    {
        cout << n << " ";
    }
    cout << suffix;
}

class FastRandomEngine
{
public:
    using result_type = uint64_t;
    result_type state;

private:
    // 0以上MAX以下の整数をとる乱数 xorshift https://ja.wikipedia.org/wiki/Xorshift
    // 2step xorshift の方が計算が速いが質が悪いらしい？
    inline result_type randXor() noexcept
    {
        state ^= state << 7;
        state ^= state >> 9;

        return state;
    }

public:
    FastRandomEngine(result_type seed = 1) : state(seed)
    {
        assert(seed != 0);
    }

    inline result_type operator()() noexcept
    {
        return randXor();
    }

    static inline constexpr result_type min() noexcept
    {
        return numeric_limits<result_type>::min();
    }

    static inline constexpr result_type max() noexcept
    {
        return numeric_limits<result_type>::max();
    }

    inline constexpr double inv_max() noexcept
    {
        return 1.0 / max();
    }

    inline long long random_int(const pair<long long, long long> &min_max) noexcept
    {
        return random_int(min_max.first, min_max.second);
    }

    inline long long random_int(long long min, long long max) noexcept
    {
        long long width = max - min + 1;
        return randXor() % width + min;
    }

    inline double random_real(const pair<double, double> &min_max) noexcept
    {
        return random_real(min_max.first, min_max.second);
    }

    inline double random_real(double min, double max) noexcept
    {
        return rand01() * (max - min) + min;
    }

    // 0以上1未満の小数をとる乱数
    inline double rand01() noexcept
    {
        return randXor() * inv_max();
    }
};
FastRandomEngine rand_engine(1);

template <class T>
inline void shuffle_vector(vector<T> &v) noexcept
{
    shuffle(v.begin(), v.end(), rand_engine);
}

template <class T>
inline T random_select(const vector<T> &v) noexcept
{
    return v[rand_engine.random_int(0, v.size() - 1)];
}

inline double generate_normal(double mu, double sigma) noexcept
{
    normal_distribution<double> dist(mu, sigma);
    return dist(rand_engine);
}

class Timer
{
private:
    chrono::high_resolution_clock::time_point start_time_;
    int64_t now_process_time_;
    int64_t time_threshold_ = -1;

public:
    // 時間制限をミリ秒単位で指定してインスタンスをつくる。
    Timer() : start_time_(chrono::high_resolution_clock::now()), now_process_time_(0) {}

    // この関数を実行するとtimerの経過時間が更新される。
    // 時間取得処理にかかるわずかな時間を省略するためにこのようにしている。
    inline void update_process_time()
    {
        auto diff = chrono::high_resolution_clock::now() - this->start_time_;
        now_process_time_ = chrono::duration_cast<chrono::milliseconds>(diff).count();
    }

    inline void set_limit_time(const int64_t &time_threshold)
    {
        this->time_threshold_ = time_threshold;
    }

    inline int64_t get_process_time() const
    {
        return now_process_time_;
    }

    inline bool over_limit_time() const
    {
        return get_rest_time() < 0;
    }

    inline int64_t get_rest_time() const
    {
        return time_threshold_ - get_process_time();
    }

    inline int64_t get_limit_time() const
    {
        return time_threshold_;
    }
};
