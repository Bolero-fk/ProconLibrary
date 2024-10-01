---
title: Zobrist Hash
documentation_of: //Hash/zobrist_hash_base.hpp
---

# Zobrist Hash
Zobrist Hashは、ある数値列の各要素にランダムな値を割り当てることで、数値列の連続部分集合に対する状態の一致判定を効率的に行うための手法です。  
これにより、数値列の部分集合が同一であるか、特定の条件を満たしているかを高速に判定できます。  

ハッシュ値の取り方に関しては、以下の記事を参考にしています。  
https://drken1215.hatenablog.com/entry/2022/05/12/105000

## ZobristHashBase
ZobristHashBaseは、Zobrist Hashに関する基本的な機能を提供する抽象クラスです。  
派生クラスで共通して使用されるハッシュ計算や、インターフェースを定義しています。

### インターフェース

#### build
```cpp
virtual void build(const vector<long long>& v)
```
この関数はハッシュ列を生成する関数です。  
引数 `v` はハッシュ対象となる整数の配列です。  

#### get_range_hash
```cpp
virtual unsigned long long get_range_hash(int l, int r) 
```
この関数は、コンストラクタで入力された配列 `v` のうち、指定された範囲 $[l, r)$ の要素に対して累積ハッシュを計算して返します。

## 派生クラス
- [ParityHash](zobrist_parity_hash.md)  
指定範囲 $[l, r)$ に含まれる **数値の出現回数の偶奇** のハッシュを計算します。  
- [CountHash](zobrist_count_hash.md)  
指定範囲 $[l, r)$ に含まれる **数値の多重集合** のハッシュを計算します。  
- [TypeHash](zobrist_type_hash.md)  
範囲 $[\textcolor{red}{0}, r)$ に含まれる **数値の集合** のハッシュを計算します。  
- [CubicHash](zobrist_cubic_hash.md)  
指定範囲 $[l, r)$ に含まれる **数値の総積を因数ごとに 3 で割った余りに置き換えた値** のハッシュを計算します。
