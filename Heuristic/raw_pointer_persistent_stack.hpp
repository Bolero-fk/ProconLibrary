#include <bits/stdc++.h>

using namespace std;

template <class T>
class RawPointerPersistentStack
{
protected:
    struct History
    {
        T v;
        History *previous;
        int size = 1;
        History(const T &v, History *previous) : v(v), previous(previous)
        {
            if (previous == nullptr)
            {
                size = 1;
                return;
            }

            size = previous->size + 1;
        }

        ~History()
        {
            delete previous;
        }
    };

private:
    History *latest;

public:
    RawPointerPersistentStack() : latest(nullptr)
    {
    }

    RawPointerPersistentStack(History *latest) : latest(latest)
    {
    }

    bool empty() const
    {
        return latest == nullptr;
    }

    T top() const
    {
        assert(!empty());
        return latest->v;
    }

    void push(const T &v)
    {
        latest = new History(v, latest);
    }

    void pop()
    {
        assert(!empty());
        latest = latest->previous;
    }

    int size() const
    {
        if (empty())
        {
            return 0;
        }

        return latest->size;
    }

    vector<T> extract_values()
    {
        vector<T> result;
        auto now = PersistentStack(latest);
        while (!now.empty())
        {
            result.push_back(now.top());
            now.pop();
        }

        reverse(result.begin(), result.end());

        return result;
    }
};