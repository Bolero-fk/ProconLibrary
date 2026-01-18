---
title: ダブリング
documentation_of: //Tree/doubling.hpp
parent: Tree
---

# ダブリング

Functional Graph上で各頂点から $k$ 回後の状態や遷移先を高速に求めます。

## コンストラクタ

```cpp
template <typename T>
Doubling(int N, unsigned long long max_k)
```
遷移元のサイズ `N` と、必要な最大遷移回数 `max_k` を与えて初期化します。 `T` はコストの型です。

## add_edge

```cpp
void add_edge(int from, int to, T cost)
```

遷移元の頂点 `from` に対し、遷移先 `to` とコスト `cost` を設定します。

**制約**
* 各頂点からの遷移は 1 度だけ設定可能。

**計算量**

* $O(1)$

## init

```cpp
void init()
```

すべての頂点に対して $2^i$ 回の遷移先とその累積コストを前計算します。

**計算量**
* $O(N \log k)$

## step_forward
```cpp
pair<int, T> step_forward(int v, unsigned long long k)
```

頂点 `v` を始点として、$k$ 回遷移した後の頂点とその間の累積コストを返します。

**計算量**
* $O(\log k)$

## step_forwards
```cpp
vector<pair<int, T>> step_forwards(const vector<int> &indices, unsigned long long k)
```

複数の始点 `indices` に対して、それぞれ $k$ 回遷移した後の頂点と累積コストをまとめて返します。
各始点について `step_forward` を同時に実行するイメージです。

**計算量**
* $O(|\text{indices}| \cdot \log k)$


```cpp
vector<pair<int, T>> step_forwards(unsigned long long k)
```
すべての頂点 `0` から `N-1` を始点として、それぞれ $k$ 回遷移させた後の頂点と累積コストを返します。

**計算量**
* $O(N \log k)$
