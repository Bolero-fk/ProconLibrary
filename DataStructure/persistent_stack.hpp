#include <bits/stdc++.h>

using namespace std;

template <class T>
class PersistentStack
{
protected:
    struct History
    {
        T v;
        shared_ptr<History> previous;
        int size = 1;
        History(const T &v, shared_ptr<History> previous) : v(v), previous(previous)
        {
            if (previous == nullptr)
            {
                size = 1;
                return;
            }

            size = previous->size + 1;
        }
    };

private:
    shared_ptr<History> latest;

public:
    PersistentStack() : latest(nullptr)
    {
    }

    PersistentStack(shared_ptr<History> latest) : latest(latest)
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
        latest = make_shared<History>(v, latest);
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