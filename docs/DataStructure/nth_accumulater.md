---
title: n次元累積和
documentation_of: //DataStructure/nth_accumulater.hpp
---

# n次元累積和
入力された`D`次元のデータの累積和を計算します。  

## コンストラクタ

```cpp
nthAccumulater<T, int D>(const vector<...>& v)
```
型`T`を要素に持つ`D`次元ベクトル`v`からなる累積和を計算します。  
次元に応じて適切な累積和が構築されます。

**計算量**
- $O(\text{vの要素数})$

## get
```cpp
T get(const vector<int>& indexes)
```
指定されたインデックスに対応する値を取得します。

**制約**
- `indexes`の次元は`D`
- 全ての`i`に対して $0 \leq \text{indexes[i]} \lt \text{sizes[i]}$


**計算量**
- $O(1)$

## set
```cpp
void set(const vector<int>& indexes, const T& value)
```
指定されたインデックスに対応する値を設定します。

**制約**
- `indexes`の次元は`D`
- 全ての`i`に対して $0 \leq \text{indexes[i]} \lt \text{sizes[i]}$

**計算量**
- $O(1)$

## sum
```cpp
T sum(vector<long long> l, vector<long long> r)
```
指定された範囲 $[l, r)$ （`l`以上`r`未満） の累積和を返します。

**制約**
- `l`と`r`の次元は`D`
- 全ての`i`に対して $0 \leq l[i] \lt r[i] \leq sizes[i]$

**計算量**
- $O(2^\text{D})$

## cyclic_sum
```cpp
T cyclic_sum(vector<long long> l, vector<long long> r)
```
入力が無限に連結されると仮定して指定された範囲 $[l, r)$ （`l`以上`r`未満） の累積和を返します。

**制約**
- `l`と`r`の次元は`D`
- 全ての`i`に対して $l[i] \lt r[i]$

**計算量**
- $O(2^\text{D})$