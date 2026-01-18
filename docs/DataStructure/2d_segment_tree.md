---
title: 二次元セグメント木
documentation_of: //DataStructure/2d_segment_tree.hpp
parent: Data Structure
nav_order: 8
---

# 二次元セグメント木

2 次元グリッド（高さ `H`、幅 `W`）上の値に対して、1点更新と長方形領域のモノイド積（集約）を行うデータ構造です。  

- `set(h, w, x)`：座標 `(h, w)` の値を `x` に更新（0-indexed）
- `get(h, w)`：座標 `(h, w)` の値を取得
- `prod(t, l, d, r)`：長方形 `[t, d) × [l, r)` のモノイド積を取得（半開区間）

`op` と `e` により定義されるモノイド（結合的演算 + 単位元）に対して動作します。

## コンストラクタ

### サイズ指定で初期化
```cpp
segtree2d(int h, int w)
```

高さ `h`、幅 `w` の 2D 配列を、すべて `e()` で初期化します。

**制約**
- $0 \leq h$
- $0 \leq w$

**計算量**
- $O(HW)$

---

### 2 次元配列から構築

```cpp
segtree2d(const vector<vector<S>>& v)
```

`v`（サイズ `H × W`）から構築します。

**制約**
- `v.size() == H`
- `v[i].size() == W` がすべての `i` で成り立つこと（長方形配列）

**計算量**
- $O(HW)$

## set

```cpp
void set(int p_h, int p_w, S x)
```

座標 `(p_h, p_w)`（0-indexed）を `x` に更新します。

**制約**
- $0 \leq p_h < H$
- $0 \leq p_w < W$

**計算量**
- $O(\log H \log W)$

## get

```cpp
S get(int p_h, int p_w) const
```

座標 `(p_h, p_w)`（0-indexed）の値を返します。

**制約**
- $0 \leq p_h < H$
- $0 \leq p_w < W$

**計算量**
- $O(1)$

---

## prod

```cpp
S prod(int t, int l, int d, int r) const
```

長方形領域 `[t, d) × [l, r)`（0-indexed, 半開区間）のモノイド積を返します。  
領域が空（`t == d` または `l == r`）の場合は `e()` を返します。

**制約**
- $0 \leq t \leq d \leq H$
- $0 \leq l \leq r \leq W$

**計算量**
- $O(\log H \log W)$
