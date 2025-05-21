---
title: Heavy-Light 分解 (HLD)
documentation_of: //DataStructure/heavy_light_decomposition.hpp
parent: Tree
nav_order: 4
---

# Heavy-Light 分解

木（無向連結グラフ）に対し、以下の操作を行います。

* 任意のパス上の区間クエリ（非可換クエリ対応）
* 任意の根付き部分木の区間クエリ
* 最小共通祖先（LCA）計算

## コンストラクタ

```cpp
HeavyLightDecomposition hld(int n);
```

* 頂点数 $n$ の木を扱うためのオブジェクトを生成します。

**計算量**

* $O(n)$

## add_edge

```cpp
void hld.add_edge(int u, int v);
```

* 頂点 $u, v$ 間に無向辺を追加します。

**制約**

* $0 \leq u, v < n$

**計算量**

* $O(1)$

## build

```cpp
void hld.build(int root = 0);
```

番号が $root$ の頂点を根として Heavy-Light 分解を構築します。
build 前提のメソッド呼び出し時は自動的に実行されます。

**制約**

* $0 \leq root < n$

**計算量**

* $O(n)$

## get_path_ranges
```cpp
std::vector<std::tuple<int, int, bool>> hld.get_path_ranges(int u, int v);
```

頂点 $u$ から $v$ へのパスをセグメントのリストに変換します。

各タプルは `(l, r, is_reverse)` の形式で、基底配列上の区間 `[l, r)` と、クエリ方向を示すフラグ `is_reverse`（`false`: 左から右へ適用、`true`: 右から左へ適用）を表します。

非可換クエリに対応する場合、is_reverse に応じてクエリや更新の適用方向を変更してください。

**制約**

* $0 \leq u, v < n$

**計算量**

* $O(\log^2 n)$

## get_subtree_range

```cpp
std::array<int, 2> hld.get_subtree_range(int u);
```

頂点 $u$ を根とする部分木を、基底配列上の区間 `[l, r)` で返します。

**制約**

* $0 \leq u < n$

**計算量**

* $O(1)$

## lca

```cpp
int hld.lca(int u, int v);
```

頂点 $u, v$ の最小共通祖先を返します。

**制約**

* $0 \leq u, v < n$

**計算量**

* $O(\log n)$

## get_pos

```cpp
int hld.get_pos(int v);
```

点 $v$ の HLD 基底配列上のインデックスを返します。

**制約**

* $0 \leq v < n$

**計算量**

* $O(1)$

## get_parent

```cpp
int hld.get_parent(int v);
```

頂点 $v$ の親ノードを返します。

**制約**

* $0 \leq v < n$

**計算量**

* $O(1)$

## get_subtree_size

```cpp
int hld.get_subtree_size(int u);
```

頂点 $u$ を根とする部分木の頂点数を返します。

**制約**

* $0 \leq u < n$

**計算量**

* $O(1)$
