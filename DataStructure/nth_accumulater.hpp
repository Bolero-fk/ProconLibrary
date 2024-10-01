#include <bits/stdc++.h>
using namespace std;

template <typename T, int DIMENSION_SIZE>
class nthAccumulater
{
private:
    vector<T> values;
    vector<int> sizes;
    int sum_size;

    void init()
    {
        sum_size = 1;
        for (auto size : sizes)
        {
            assert(0 < size);
            sum_size *= size;
        }

        assert(0 < sum_size);
        values.resize(sum_size);
    }

    int get_index(const vector<int> &indexes)
    {
        assert((int)indexes.size() == DIMENSION_SIZE);

        int base = 1;
        int index = 0;
        for (int i = 0; i < DIMENSION_SIZE; i++)
        {
            index += indexes[i] * base;
            base *= sizes[i];
        }

        return index;
    }

    vector<int> get_index(int index)
    {
        assert(0 <= index && index < sum_size);

        vector<int> indexes(DIMENSION_SIZE);

        for (int i = 0; i < DIMENSION_SIZE; i++)
        {
            indexes[i] = index % sizes[i];
            index /= sizes[i];
        }

        return indexes;
    }

    void build()
    {
        for (int dimension = 0; dimension < DIMENSION_SIZE; dimension++)
        {
            for (int i = 0; i < sum_size; i++)
            {
                vector<int> index = get_index(i);
                if (index[dimension] == sizes[dimension] - 1)
                {
                    continue;
                }
                vector<int> next_index = index;
                next_index[dimension]++;
                set(next_index, get(index) + get(next_index));
            }
        }
    }

    T sum_from_origin(const vector<int> &indexes)
    {
        assert((int)indexes.size() == DIMENSION_SIZE);

        T result = 0;
        vector<T> counts(DIMENSION_SIZE);
        for (int i = 0; i < DIMENSION_SIZE; i++)
        {
            counts[i] = indexes[i] / (sizes[i] - 1);
        }

        for (unsigned int bit = 0; bit < (1 << DIMENSION_SIZE); bit++)
        {
            T count = 1;
            vector<int> query_index(DIMENSION_SIZE);
            for (int i = 0; i < DIMENSION_SIZE; i++)
            {
                if ((bit >> i) & 1)
                {
                    count *= 1;
                    query_index[i] = indexes[i] % (sizes[i] - 1);
                }
                else
                {
                    count *= counts[i];
                    query_index[i] = sizes[i] - 1;
                }
            }

            result += count * get(query_index);
        }

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
            sizes[depth] = v.size() + 1;
            set_sizes(v[0], depth + 1);
        }
    }

    template <typename V>
    void set_values(const V &v, vector<int> &index, int depth = 0)
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
        sizes.resize(DIMENSION_SIZE, 0);
        set_sizes(v);

        init();
        vector<int> index(DIMENSION_SIZE);
        set_values(v, index);
        build();
    }

    T get(const vector<int> &indexes)
    {
        assert((int)indexes.size() == DIMENSION_SIZE);

        int index = get_index(indexes);
        return get(index);
    }

    T get(const int &index)
    {
        assert(0 <= index && index < sum_size);

        return values[index];
    }

    void set(const vector<int> &indexes, const T &value)
    {
        assert((int)indexes.size() == DIMENSION_SIZE);

        int index = get_index(indexes);
        set(index, value);
    }

    void set(const int &index, const T &value)
    {
        assert(0 <= index && index < sum_size);

        values[index] = value;
    }

    T sum(vector<long long> l, vector<long long> r)
    {
        assert((int)l.size() == DIMENSION_SIZE && (int)r.size() == DIMENSION_SIZE);
        for (int i = 0; i < DIMENSION_SIZE; i++)
        {
            assert(0 <= l[i] && r[i] <= sizes[i]);
        }

        return cyclic_sum(l, r);
    }

    T cyclic_sum(vector<long long> l, vector<long long> r)
    {
        assert((int)l.size() == DIMENSION_SIZE && (int)r.size() == DIMENSION_SIZE);
        for (int i = 0; i < DIMENSION_SIZE; i++)
        {
            assert(l[i] < r[i]);
        }

        // lの値が負数の場合、正数に変換する
        for (int i = 0; i < DIMENSION_SIZE; i++)
        {
            if (l[i] < 0)
            {
                long long mod = sizes[i] - 1;
                long long next_l = (l[i] % mod + mod) % mod;
                r[i] += next_l - l[i];
                l[i] = next_l;
            }
        }

        T result = 0;
        for (unsigned int bit = 0; bit < (1 << DIMENSION_SIZE); bit++)
        {
            vector<int> indexes(DIMENSION_SIZE);
            for (int i = 0; i < DIMENSION_SIZE; i++)
            {
                indexes[i] = ((bit >> i) & 1) ? r[i] : l[i];
            }

            int one_count = popcount(bit);
            T sign = (one_count % 2) == (DIMENSION_SIZE % 2) ? 1 : -1;
            result += sign * sum_from_origin(indexes);
        }

        return result;
    }
};
