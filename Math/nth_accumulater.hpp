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

public:
    nthAccumulater(const vector<T> &v)
    {
        assert(DIMENSION_SIZE == 1);

        sizes = {(int)v.size() + 1};
        init();
        for (int i1 = 0; i1 < (int)v.size(); i1++)
        {
            set({i1 + 1}, v[i1]);
        }
        build();
    }

    nthAccumulater(const vector<vector<T>> &v)
    {
        assert(DIMENSION_SIZE == 2);

        sizes = {(int)v.size() + 1, (int)v[0].size() + 1};
        init();
        for (int i1 = 0; i1 < (int)v.size(); i1++)
        {
            for (int i2 = 0; i2 < (int)v[0].size(); i2++)
            {
                set({i1 + 1, i2 + 1}, v[i1][i2]);
            }
        }

        build();
    }

    nthAccumulater(const vector<vector<vector<T>>> &v)
    {
        assert(DIMENSION_SIZE == 3);

        sizes = {(int)v.size() + 1, (int)v[0].size() + 1, (int)v[0][0].size() + 1};
        init();
        for (int i1 = 0; i1 < (int)v.size(); i1++)
        {
            for (int i2 = 0; i2 < (int)v[0].size(); i2++)
            {
                for (int i3 = 0; i3 < (int)v[0][0].size(); i3++)
                {
                    set({i1 + 1, i2 + 1, i3 + 1}, v[i1][i2][i3]);
                }
            }
        }
        build();
    }

    nthAccumulater(const vector<vector<vector<vector<T>>>> &v)
    {
        assert(DIMENSION_SIZE == 4);

        sizes = {(int)v.size() + 1, (int)v[0].size() + 1, (int)v[0][0].size() + 1, (int)v[0][0][0].size() + 1};
        init();
        for (int i1 = 0; i1 < (int)v.size(); i1++)
        {
            for (int i2 = 0; i2 < (int)v[0].size(); i2++)
            {
                for (int i3 = 0; i3 < (int)v[0][0].size(); i3++)
                {
                    for (int i4 = 0; i4 < (int)v[0][0][0].size(); i4++)
                    {
                        set({i1 + 1, i2 + 1, i3 + 1, i4 + 1}, v[i1][i2][i3][i4]);
                    }
                }
            }
        }
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
