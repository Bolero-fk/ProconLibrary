---
title: KDTree
documentation_of: //DataStructure/kd_tree.hpp
parent: Data Structure
---

# KDTree
K 次元空間の点群から k-d tree を構築し、高速に最近傍検索や範囲検索を行うデータ構造です。  
構築には平均で $O(N \log N)$ の時間がかかるため、点群の動的な追加・削除にはあまり向いていません。    
一方、一度構築してしまえば、最近傍検索や範囲検索を平均 $O(\log N)$ で実行できます。

## テンプレートパラメータ

```cpp
template <typename T, size_t K>
```

- `T`: 座標の型（数値型）
- `K`: 次元数

## 検索結果

### PointWithID

```cpp
struct PointWithID {
    array<T, K> point;
    size_t id;
};
```

kd木による検索結果は座標 `point` と一意な識別子 `id` をまとめた構造体によって返されます。
`id` は追加された順に割り振られます。

## コンストラクタ

```cpp
KDTree(const vector<array<T, K>> &points)
```

点群 `points` から k-d tree を構築します。各点には入力順に `0` から `points.size()-1` までの `id` が自動付与されます。

**計算量**
* 平均: $O(N \log N)$

## 最近傍検索 (nearest)

```cpp
optional<PointWithID> nearest(
    const array<T, K> &target,
    function<bool(int)> check) const
```

フィルタ関数 `check(id)` が `true` の点の中から、`target` に最も近い点を返します。該当点がない場合は `nullopt`が返されます。

**計算量**
* 平均: $O(\log N)$

```cpp
optional<PointWithID> nearest(
    const array<T, K> &target) const
```

`check` なし版。全点を対象に探索します。

**計算量**
* 平均: $O(\log N)$

## 範囲検索 (range_search)

```cpp
vector<PointWithID> range_search(
    const array<T, K> &lower,
    const array<T, K> &upper,
    function<bool(int)> check) const
```

矩形領域 `[lower, upper]` 内に含まれる点を返します。`check(id)` で追加フィルタが可能です。

**計算量**
* 平均: $O(R + \log N)$  
  - $R$: 結果点数

```cpp
vector<PointWithID> range_search(
    const array<T, K> &lower,
    const array<T, K> &upper) const
```

`check` なし版。

## k 個の最近傍検索 (nearest_k)

```cpp
vector<PointWithID> nearest_k(
    const array<T, K> &target,
    size_t k,
    function<bool(int)> check) const
```

`target` に近い点を最大 `k` 個返します。`check(id)` でフィルタが可能です。

**計算量**
* 平均: $O(k \log N)$

```cpp
vector<PointWithID> nearest_k(
    const array<T, K> &target,
    size_t k) const
```

`check` なし版。
