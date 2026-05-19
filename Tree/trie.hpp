#include <bits/stdc++.h>
using namespace std;

template <class T>
struct Trie
{
    struct Node
    {
        // 子ノードへの遷移
        unordered_map<T, int> next_node_ids;

        // 親ノードのID
        // root の parent は -1
        int parent = -1;

        // parent からこのノードへ遷移するときに使った値
        // root では意味を持たない
        T transition_value{};

        // このノードを通過する文字列の個数
        int pass_count = 0;

        // このノードで終端する文字列の個数
        int end_count = 0;

        Node() {};

        Node(int parent, const T &transition_value)
            : parent(parent), transition_value(transition_value) {};
    };

    vector<Node> nodes;

    Trie() : nodes()
    {
        nodes.push_back(Node());
    };

    template <typename Container>
        requires same_as<typename Container::value_type, T>
    int insert(const Container &v)
    {
        int node_id = 0;
        nodes[node_id].pass_count++;

        for (const auto &c : v)
        {
            if (!nodes[node_id].next_node_ids.contains(c))
            {
                int next_node_id = nodes.size();
                nodes[node_id].next_node_ids[c] = next_node_id;

                // 新しく作るノードは、現在のノードを親として持つ
                nodes.push_back(Node(node_id, c));
            }

            node_id = nodes[node_id].next_node_ids[c];
            nodes[node_id].pass_count++;
        }

        nodes[node_id].end_count++;

        // 挿入した列に対応する終端ノードIDを返す
        return node_id;
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

            // 第2引数は、現在のノードが入力列 v の終端かどうか
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

        // prefix 以下の部分木を論理的に削除する
        nodes[node_id].pass_count = 0;
        nodes[node_id].end_count = 0;
        nodes[node_id].next_node_ids.clear();

        // 祖先の通過回数から、削除した部分木の通過回数を引く
        for (const auto &ancestor : ancestors)
        {
            nodes[ancestor].pass_count -= removed_pass_count;
        }
    }
};