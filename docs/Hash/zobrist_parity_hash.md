---
title: ZobristHash (偶奇判定)
documentation_of: //Hash/zobrist_parity_hash.hpp
---

# ZobristParityHash
`ZobristParityHash` は、Zobrist Hash を用いて指定範囲の数値列に含まれる  **数値の出現回数の偶奇** のハッシュ値を計算するクラスです。  

## コンストラクタ
```cpp
ZobristParityHash(const vector<long long>& v)
```

数値列 `v` 全体の累積ハッシュを初期化します。

**計算量**
- $O(N)$

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