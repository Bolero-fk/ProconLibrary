#include <bits/stdc++.h>
using namespace std;

template <typename T, int DIMENSION_SIZE>
class nthAccumulater
{
private:
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
            sum_size *= sizes[i] + 1; // 0が含まれるので+1する
        }
        sum_sizes[DIMENSION_SIZE] = sum_size;

        assert(0 < sum_size);
        values.resize(sum_size);
    }

    int get_index(const array<int, DIMENSION_SIZE> &indexes)
    {
        int result = 0;
        for (int i = 0; i < DIMENSION_SIZE; i++)
        {
            result += indexes[i] * sum_sizes[i];
        }

        return result;
    }

    array<int, DIMENSION_SIZE> get_index(int index)
    {
        assert(0 <= index && index < sum_sizes[DIMENSION_SIZE]);

        array<int, DIMENSION_SIZE> indexes;

        for (int i = 0; i < DIMENSION_SIZE; i++)
        {
            indexes[i] = index % (sizes[i] + 1);
            index /= (sizes[i] + 1);
        }

        return indexes;
    }

    void build()
    {
        for (int dimension = 0; dimension < DIMENSION_SIZE; dimension++)
        {
            for (int i = 0; i < sum_sizes[DIMENSION_SIZE]; i++)
            {
                array<int, DIMENSION_SIZE> index = get_index(i);
                if (index[dimension] == sizes[dimension])
                {
                    continue;
                }
                array<int, DIMENSION_SIZE> next_index = index;
                next_index[dimension]++;
                set(next_index, get(index) + get(next_index));
            }
        }
    }

    T sum_from_origin(const unsigned int &bit_mask, const array<long long, DIMENSION_SIZE> &indexes)
    {
        T result = 0;

        unsigned int sub_bit = bit_mask;
        do
        {
            T count = 1;
            array<int, DIMENSION_SIZE> query_index;
            for (int i = 0; i < DIMENSION_SIZE; i++)
            {
                if ((sub_bit >> i) & 1)
                {
                    count *= indexes[i] / sizes[i];
                    query_index[i] = sizes[i];
                }
                else
                {
                    count *= 1;
                    query_index[i] = indexes[i] % sizes[i];
                }
            }

            result += count * get(query_index);

            sub_bit = (sub_bit - 1) & bit_mask;
        } while (sub_bit != bit_mask);

        return result;
    }

    template <typename V>
    void set_sizes(const V &v, int depth = 0)
    {
        if constexpr (is_arithmetic_v<V>)
        {
            return;
        }
        else
        {
            sizes[depth] = v.size();
            set_sizes(v[0], depth + 1);
        }
    }

    template <typename V>
    void set_values(const V &v, array<int, DIMENSION_SIZE> &index, int depth = 0)
    {
        if constexpr (is_arithmetic_v<V>)
        {
            set(index, v);
            return;
        }
        else
        {
            for (int i = 0; i < (int)v.size(); ++i)
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
        array<int, DIMENSION_SIZE> index;
        set_values(v, index);
        build();
    }

    T get(const array<int, DIMENSION_SIZE> &indexes)
    {
        int index = get_index(indexes);
        return get(index);
    }

    T get(const int &index)
    {
        assert(0 <= index && index < sum_sizes[DIMENSION_SIZE]);

        return values[index];
    }

    void set(const array<int, DIMENSION_SIZE> &indexes, const T &value)
    {
        int index = get_index(indexes);
        set(index, value);
    }

    void set(const int &index, const T &value)
    {
        assert(0 <= index && index < sum_sizes[DIMENSION_SIZE]);

        values[index] = value;
    }

    T sum(const array<long long, DIMENSION_SIZE> &l, const array<long long, DIMENSION_SIZE> &r)
    {
        for (int i = 0; i < DIMENSION_SIZE; i++)
        {
            assert(0 <= l[i] && l[i] < r[i] && r[i] <= sizes[i]);
        }

        T result = 0;
        for (unsigned int bit = 0; bit < (1 << DIMENSION_SIZE); bit++)
        {
            int index = 0;
            for (int i = 0; i < DIMENSION_SIZE; i++)
            {
                index += (((bit >> i) & 1) ? r[i] : l[i]) * sum_sizes[i];
            }

            int one_count = popcount(bit);
            T sign = (one_count % 2) == (DIMENSION_SIZE % 2) ? 1 : -1;
            result += sign * get(index);
        }

        return result;
    }

    T cyclic_sum(array<long long, DIMENSION_SIZE> l, array<long long, DIMENSION_SIZE> r)
    {
        for (int i = 0; i < DIMENSION_SIZE; i++)
        {
            assert(l[i] < r[i]);
        }

        // lの値が負数の場合、正数に変換する
        for (int i = 0; i < DIMENSION_SIZE; i++)
        {
            if (l[i] < 0)
            {
                long long mod = sizes[i];
                long long next_l = (l[i] % mod + mod) % mod;
                r[i] += next_l - l[i];
                l[i] = next_l;
            }
        }

        T result = 0;
        for (unsigned int bit = 0; bit < (1 << DIMENSION_SIZE); bit++)
        {
            array<long long, DIMENSION_SIZE> indexes;

            unsigned int bit_mask = 0;

            for (int i = 0; i < DIMENSION_SIZE; i++)
            {
                indexes[i] = ((bit >> i) & 1) ? r[i] : l[i];

                if (sizes[i] <= indexes[i])
                {
                    bit_mask |= (1 << i);
                }
            }

            int one_count = popcount(bit);
            T sign = (one_count % 2) == (DIMENSION_SIZE % 2) ? 1 : -1;
            result += sign * sum_from_origin(bit_mask, indexes);
        }

        return result;
    }
};
