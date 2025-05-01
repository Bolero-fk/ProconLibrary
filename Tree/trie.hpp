#include <bits/stdc++.h>
using namespace std;

template <class T>
struct Trie
{
    struct Node
    {
        unordered_map<T, int> next_node_ids;
        int pass_count = 0;
        int end_count = 0;

        Node() {};
    };

    vector<Node> nodes;
    Trie() : nodes()
    {
        nodes.push_back(Node());
    };

    template <typename Container>
        requires same_as<typename Container::value_type, T>
    void insert(const Container &v)
    {
        int node_id = 0;
        nodes[node_id].pass_count++;
        for (const auto &c : v)
        {
            if (!nodes[node_id].next_node_ids.contains(c))
            {
                nodes[node_id].next_node_ids[c] = nodes.size();
                nodes.push_back(Node());
            }

            node_id = nodes[node_id].next_node_ids[c];
            nodes[node_id].pass_count++;
        }

        nodes[node_id].end_count++;
    }

    template <typename Container, typename Func>
        requires same_as<typename Container::value_type, T> && invocable<Func, int, bool>
    void iterate_prefix(const Container &v, Func f)
    {
        int node_id = 0;
        for (auto itr = v.begin(); itr != v.end(); itr++)
        {
            if (!nodes[node_id].next_node_ids.contains(*itr))
            {
                return;
            }

            node_id = nodes[node_id].next_node_ids[*itr];
            f(node_id, next(itr) == v.end());
        }
    }

    template <typename Container>
        requires same_as<typename Container::value_type, T>
    void erase_subtrie(const Container &prefix)
    {
        int node_id = 0;
        vector<int> ancestors;
        for (const auto &c : prefix)
        {
            ancestors.push_back(node_id);
            if (!nodes[node_id].next_node_ids.contains(c))
            {
                return;
            }

            node_id = nodes[node_id].next_node_ids[c];
        }

        int removed_pass_count = nodes[node_id].pass_count;
        nodes[node_id].pass_count = 0, nodes[node_id].end_count = 0;
        nodes[node_id].next_node_ids.clear();

        for (const auto &ancestor : ancestors)
        {
            nodes[ancestor].pass_count -= removed_pass_count;
        }
    }
};
