#include <bits/stdc++.h>
using namespace std;

template <typename T, size_t K>
class KDTree
{
public:
    // 座標と id をまとめた構造体
    struct PointWithID
    {
        array<T, K> point;
        size_t id;
    };

    // ノードは PointWithID の情報を持つ
    struct Node
    {
        PointWithID data;
        Node *left;
        Node *right;
        Node(const PointWithID &pwid)
            : data(pwid), left(nullptr), right(nullptr) {}
    };

    // コンストラクタ: 点群から kd 木を構築
    KDTree(const vector<array<T, K>> &points)
    {
        vector<PointWithID> pts;
        pts.reserve(points.size());
        for (size_t i = 0; i < points.size(); ++i)
        {
            pts.push_back({points[i], i});
        }
        root = build(pts.begin(), pts.end(), 0);
    }

    ~KDTree()
    {
        free_tree(root);
    }

    optional<PointWithID> nearest(const array<T, K> &target,
                                  function<bool(int)> check) const
    {
        Node *best = nullptr;
        T bestDist = numeric_limits<T>::max();
        nearest_search(root, target, 0, best, bestDist, check);
        if (best)
            return best->data;
        else
            return nullopt;
    }

    optional<PointWithID> nearest(const array<T, K> &target) const
    {
        return nearest(target, [](int)
                       { return true; });
    }

    vector<PointWithID> range_search(const array<T, K> &lower, const array<T, K> &upper,
                                     function<bool(int)> check) const
    {
        vector<PointWithID> results;
        range_search(root, 0, lower, upper, check, results);
        return results;
    }

    vector<PointWithID> range_search(const array<T, K> &lower, const array<T, K> &upper) const
    {
        return range_search(lower, upper, [](int)
                            { return true; });
    }

private:
    using iterator = typename vector<PointWithID>::iterator;
    Node *root = nullptr;

    // kd木の構築 (中央値による分割)
    Node *build(iterator begin, iterator end, size_t depth)
    {
        if (begin >= end)
            return nullptr;
        size_t axis = depth % K;
        iterator mid = begin + distance(begin, end) / 2;
        nth_element(begin, mid, end, [axis](const PointWithID &a, const PointWithID &b)
                    { return a.point[axis] < b.point[axis]; });
        Node *node = new Node(*mid);
        node->left = build(begin, mid, depth + 1);
        node->right = build(mid + 1, end, depth + 1);
        return node;
    }

    // 再帰的な最近傍探索
    void nearest_search(Node *node, const array<T, K> &target, size_t depth,
                        Node *&best, T &bestDist, function<bool(int)> check) const
    {
        if (node == nullptr)
            return;
        size_t axis = depth % K;
        T d = distance_squared(node->data.point, target);

        if (d < bestDist && check(static_cast<int>(node->data.id)))
        {
            bestDist = d;
            best = node;
        }
        T diff = target[axis] - node->data.point[axis];
        Node *nearChild = (diff < 0) ? node->left : node->right;
        Node *farChild = (diff < 0) ? node->right : node->left;
        nearest_search(nearChild, target, depth + 1, best, bestDist, check);
        if (diff * diff < bestDist)
            nearest_search(farChild, target, depth + 1, best, bestDist, check);
    }

    // 再帰的な範囲探索
    void range_search(Node *node, size_t depth,
                      const array<T, K> &lower, const array<T, K> &upper,
                      function<bool(int)> check, vector<PointWithID> &results) const
    {
        if (node == nullptr)
            return;
        bool inside = true;
        for (size_t i = 0; i < K; i++)
        {
            if (node->data.point[i] < lower[i] || node->data.point[i] > upper[i])
            {
                inside = false;
                break;
            }
        }
        if (inside && check(static_cast<int>(node->data.id)))
            results.push_back(node->data);

        size_t axis = depth % K;
        if (lower[axis] <= node->data.point[axis])
            range_search(node->left, depth + 1, lower, upper, check, results);
        if (upper[axis] >= node->data.point[axis])
            range_search(node->right, depth + 1, lower, upper, check, results);
    }

    // 2点間の二乗距離を計算
    T distance_squared(const array<T, K> &a, const array<T, K> &b) const
    {
        T dist = 0;
        for (size_t i = 0; i < K; i++)
        {
            T d = a[i] - b[i];
            dist += d * d;
        }
        return dist;
    }

    // kd木のメモリ解放
    void free_tree(Node *node)
    {
        if (node == nullptr)
            return;
        free_tree(node->left);
        free_tree(node->right);
        delete node;
    }
};