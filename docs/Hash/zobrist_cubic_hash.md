---
title: ZobristHash (立方数判定)
documentation_of: //Hash/zobrist_cubic_hash.hpp
---

# ZobristCubicHash
`ZobristCubicHash` は、Zobrist Hash を用いて指定範囲の数値列に含まれる  **数値の総積を因数ごとに 3 で割った余りに置き換えた値** のハッシュ値を計算するクラスです。  
累積ハッシュ値が 0 のとき、指定範囲の値の総積は立方数であると判定できます。  

## コンストラクタ
```cpp
ZobristCubicHash(const vector<long long>& v)
```

数値列 `v` 全体の累積ハッシュを初期化します。

**計算量**
v に含まれる要素の最大値をMとしたとき
- $O(N \log M)$

## get_range_hash
```cpp
unsigned long long get_range_hash(int l, int r)
```
指定された範囲 `[l, r)` の数値列に含まれる要素の累積ハッシュ値を返します。

**制約**
配列`v`の大きさを`N`としたとき
- $0 \leq l \lt r \leq N $

**計算量**
- $O(1)$

## 関連情報
- [ZobristHashBase](zobrist_hash_base.hpp): 基底クラス