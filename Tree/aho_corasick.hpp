#include <bits/stdc++.h>
using namespace std;

#include "Tree/trie.hpp"

template <class T>
struct AhoCorasick
{
    Trie<T> trie;

    // suffix_link[v]:
    // str(v) の真の接尾辞のうち、Trie に存在する最長のものに対応するノードID
    vector<int> suffix_link;

    // matched[v]:
    // v に到達した時点で、何らかの登録済みパターンが末尾にマッチしているか
    vector<bool> matched;

    // build 後に true
    bool built = false;

    AhoCorasick() = default;

    template <typename Container>
        requires same_as<typename Container::value_type, T>
    int insert(const Container &pattern)
    {
        built = false;
        return trie.insert(pattern);
    }

    void build()
    {
        const int node_count = trie.nodes.size();

        suffix_link.assign(node_count, 0);
        matched.assign(node_count, false);

        for (int node_id = 0; node_id < node_count; node_id++)
        {
            matched[node_id] = trie.nodes[node_id].end_count > 0;
        }

        queue<int> que;

        // root の子の suffix link は root
        for (const auto &[value, child] : trie.nodes[0].next_node_ids)
        {
            suffix_link[child] = 0;
            que.push(child);
        }

        while (!que.empty())
        {
            int node_id = que.front();
            que.pop();

            // suffix link 先でマッチしているなら、このノードもマッチ状態
            matched[node_id] = matched[node_id] || matched[suffix_link[node_id]];

            for (const auto &[value, child] : trie.nodes[node_id].next_node_ids)
            {
                suffix_link[child] = find_next(suffix_link[node_id], value);
                que.push(child);
            }
        }

        built = true;
    }

    int move(int node_id, const T &value) const
    {
        assert(built);

        return find_next(node_id, value);
    }

    bool is_matched(int node_id) const
    {
        assert(built);

        return matched[node_id];
    }

    int get_suffix_link(int node_id) const
    {
        assert(built);

        return suffix_link[node_id];
    }

    int parent(int node_id) const
    {
        return trie.nodes[node_id].parent;
    }

    T transition_value(int node_id) const
    {
        return trie.nodes[node_id].transition_value;
    }

    int size() const
    {
        return trie.nodes.size();
    }

private:
    int find_next(int node_id, const T &value) const
    {
        while (node_id != 0 && !trie.nodes[node_id].next_node_ids.contains(value))
        {
            node_id = suffix_link[node_id];
        }

        if (trie.nodes[node_id].next_node_ids.contains(value))
        {
            return trie.nodes[node_id].next_node_ids.at(value);
        }

        return 0;
    }
};