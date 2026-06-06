#include <bits/stdc++.h>
using namespace std;

template <typename T, int DIMENSION_SIZE>
class nthAccumulater
{
private:
    static_assert(0 < DIMENSION_SIZE, "DIMENSION_SIZE must be positive.");

    vector<T> values;
    array<int, DIMENSION_SIZE> sizes;
    array<int, DIMENSION_SIZE + 1> sum_sizes;

    void init()
    {
        int sum_size = 1;

        for (int i = 0; i < DIMENSION_SIZE; i++)
        {
            assert(0 < sizes[i]);

            sum_sizes[i] = sum_size;
            sum_size *= sizes[i] + 1; // 累積和用に 0 番目を追加するため +1 する
        }

        sum_sizes[DIMENSION_SIZE] = sum_size;

        assert(0 < sum_size);
        values.assign(sum_size, T{});
    }

    int get_index(const array<int, DIMENSION_SIZE> &indexes) const
    {
        int result = 0;

        for (int i = 0; i < DIMENSION_SIZE; i++)
        {
            result += indexes[i] * sum_sizes[i];
        }

        return result;
    }

    int get_index(const array<long long, DIMENSION_SIZE> &indexes) const
    {
        int result = 0;

        for (int i = 0; i < DIMENSION_SIZE; i++)
        {
            result += indexes[i] * sum_sizes[i];
        }

        return result;
    }

    void build()
    {
        const int total_size = sum_sizes[DIMENSION_SIZE];

        for (int dimension = 0; dimension < DIMENSION_SIZE; dimension++)
        {
            const int stride = sum_sizes[dimension];
            const int width = sizes[dimension] + 1;
            const int block_size = stride * width;

            for (int block = 0; block < total_size; block += block_size)
            {
                for (int offset = 0; offset < stride; offset++)
                {
                    for (int k = 1; k <= sizes[dimension]; k++)
                    {
                        const int now = block + k * stride + offset;
                        values[now] += values[now - stride];
                    }
                }
            }
        }
    }

    T sum_from_origin(const unsigned int bit_mask, const array<long long, DIMENSION_SIZE> &indexes) const
    {
        T result = T{};
        unsigned int sub_bit = bit_mask;

        do
        {
            T count = T{1};
            array<int, DIMENSION_SIZE> query_index{};

            for (int i = 0; i < DIMENSION_SIZE; i++)
            {
                if ((sub_bit >> i) & 1u)
                {
                    count *= indexes[i] / sizes[i];
                    query_index[i] = sizes[i];
                }
                else
                {
                    query_index[i] = indexes[i] % sizes[i];
                }
            }

            result += count * get(query_index);

            sub_bit = (sub_bit - 1) & bit_mask;
        } while (sub_bit != bit_mask);

        return result;
    }

    template <typename V>
    void set_sizes(const V &v, const int depth = 0)
    {
        if constexpr (is_arithmetic_v<V>)
        {
            return;
        }
        else
        {
            assert(!v.empty());

            sizes[depth] = v.size();
            set_sizes(v[0], depth + 1);
        }
    }

    template <typename V>
    void set_values(const V &v, array<int, DIMENSION_SIZE> &index, const int depth = 0)
    {
        if constexpr (is_arithmetic_v<V>)
        {
            set(index, v);
        }
        else
        {
            for (int i = 0; i < (int)v.size(); i++)
            {
                index[depth] = i + 1;
                set_values(v[i], index, depth + 1);
            }
        }
    }

public:
    template <typename V>
    nthAccumulater(const vector<V> &v)
    {
        set_sizes(v);

        init();

        array<int, DIMENSION_SIZE> index{};
        set_values(v, index);

        build();
    }

    T get(const array<int, DIMENSION_SIZE> &indexes) const
    {
        return get(get_index(indexes));
    }

    T get(const int index) const
    {
        assert(0 <= index && index < sum_sizes[DIMENSION_SIZE]);
        return values[index];
    }

    void set(const array<int, DIMENSION_SIZE> &indexes, const T &value)
    {
        set(get_index(indexes), value);
    }

    void set(const int index, const T &value)
    {
        assert(0 <= index && index < sum_sizes[DIMENSION_SIZE]);
        values[index] = value;
    }

    T sum(const array<long long, DIMENSION_SIZE> &l, const array<long long, DIMENSION_SIZE> &r) const
    {
        for (int i = 0; i < DIMENSION_SIZE; i++)
        {
            assert(0 <= l[i] && l[i] < r[i] && r[i] <= sizes[i]);
        }

        if constexpr (DIMENSION_SIZE == 1)
        {
            return values[r[0]] - values[l[0]];
        }
        else if constexpr (DIMENSION_SIZE == 2)
        {
            const int s0 = sum_sizes[0];
            const int s1 = sum_sizes[1];

            const int l0 = l[0];
            const int r0 = r[0];
            const int l1 = l[1];
            const int r1 = r[1];

            return values[r0 * s0 + r1 * s1] - values[l0 * s0 + r1 * s1] - values[r0 * s0 + l1 * s1] + values[l0 * s0 + l1 * s1];
        }
        else if constexpr (DIMENSION_SIZE == 3)
        {
            const int s0 = sum_sizes[0];
            const int s1 = sum_sizes[1];
            const int s2 = sum_sizes[2];

            const int l0 = l[0];
            const int r0 = r[0];
            const int l1 = l[1];
            const int r1 = r[1];
            const int l2 = l[2];
            const int r2 = r[2];

            auto index = [&](const int a, const int b, const int c) -> int
            {
                return a * s0 + b * s1 + c * s2;
            };

            return values[index(r0, r1, r2)] - values[index(l0, r1, r2)] - values[index(r0, l1, r2)] - values[index(r0, r1, l2)] + values[index(l0, l1, r2)] + values[index(l0, r1, l2)] + values[index(r0, l1, l2)] - values[index(l0, l1, l2)];
        }
        else
        {
            T result = T{};

            for (unsigned int bit = 0; bit < (1u << DIMENSION_SIZE); bit++)
            {
                int index = 0;

                for (int i = 0; i < DIMENSION_SIZE; i++)
                {
                    index += (((bit >> i) & 1u) ? r[i] : l[i]) * sum_sizes[i];
                }

                if ((__builtin_popcount(bit) % 2) == (DIMENSION_SIZE % 2))
                {
                    result += values[index];
                }
                else
                {
                    result -= values[index];
                }
            }

            return result;
        }
    }

    T cyclic_sum(array<long long, DIMENSION_SIZE> l, array<long long, DIMENSION_SIZE> r) const
    {
        for (int i = 0; i < DIMENSION_SIZE; i++)
        {
            assert(l[i] < r[i]);
        }

        // l の値が負数の場合、正数に変換する。
        for (int i = 0; i < DIMENSION_SIZE; i++)
        {
            if (l[i] < 0)
            {
                const long long mod = sizes[i];
                const long long next_l = (l[i] % mod + mod) % mod;

                r[i] += next_l - l[i];
                l[i] = next_l;
            }
        }

        T result = T{};

        for (unsigned int bit = 0; bit < (1u << DIMENSION_SIZE); bit++)
        {
            array<long long, DIMENSION_SIZE> indexes{};
            unsigned int bit_mask = 0;

            for (int i = 0; i < DIMENSION_SIZE; i++)
            {
                indexes[i] = ((bit >> i) & 1u) ? r[i] : l[i];

                if (sizes[i] <= indexes[i])
                {
                    bit_mask |= (1u << i);
                }
            }

            if ((__builtin_popcount(bit) % 2) == (DIMENSION_SIZE % 2))
            {
                result += sum_from_origin(bit_mask, indexes);
            }
            else
            {
                result -= sum_from_origin(bit_mask, indexes);
            }
        }

        return result;
    }
};