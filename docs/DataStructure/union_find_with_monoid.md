---
title: モノイド付きUnion Find
documentation_of: //DataStructure/union_find_with_monoid.hpp
parent: Data Structure
---

# モノイド付きUnion Find (`UnionFindWithMonoid`)
`atcoder::dsu` を継承し、結合時に関数をフックできる Union-Find です。  
成分併合の際に `op(from, to)` が一度呼び出されます。

## コンストラクタ
```cpp
UnionFindWithMonoid(int N)
```
`N` 頂点（`0..N-1`）で初期化します。

**計算量**
- $O(N)$

## merge（拡張版）
```cpp
int merge(int u, int v, std::function<void(int, int)> op)
```
頂点 `u` と `v` を属する成分同士で併合します。  
すでに同成分のときは統合を行わず、代表元 `leader(u)` を返します（`op` は呼ばれません）。  
異なる成分*ときのみ併合が実行され、内部で `atcoder::dsu::merge(u, v)` を呼び、新しい代表元を `to`、吸収される代表元を `from` として ちょうど一度 `op(from, to)` を呼びます。

- `op(from, to)` は「from の成分の情報を to の成分へ統合する」ための処理を書いてください。

**戻り値**
- 併合後の代表元 `to`（同成分だった場合は `leader(u)`）

**制約**
- `0 ≤ u, v < N`

**計算量**
- ならし $O(\alpha(N))$（アッカーマン関数の逆関数）

## その他の機能
本クラスは `atcoder::dsu` を継承しているため、以下の関数もそのまま使用できます。  
- `leader(int v)`  
- `same(int u, int v)`  
- `size(int v)`  
- `groups()`  


## 関連情報
- [AtCoder Library `dsu`](https://atcoder.github.io/ac-library/production/document_ja/dsu.html): 依存クラス

