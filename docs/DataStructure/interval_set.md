---
title: Interval Set
documentation_of: //DataStructure/interval_set.hpp
parent: Data Structure
---

# Interval Set

互いに交差しない半開区間 `[L, R)` の集合を管理するデータ構造です。  
区間の追加時には自動的に隣接・重複する区間をマージし、  
連結判定や区間長の取得、全体の長さの取得などができます。

- テンプレート引数
  - `T` : 区間端点の型
  - `Compare` : `std::set` 用の比較関数（デフォルト `std::less<T>`）
- 制約
  - `Compare` は `T` に対して `std::strict_weak_order` を満たす
  - `T` 同士の差 `T - T` と `std::abs` が利用できる（長さ計算用）
- 内部表現
  - 区間はすべて **半開区間** `[L, R)` として保存されます
  - どの 2 区間も互いに交差・隣接しないように保たれます

---

## コンストラクタ

```cpp
IntervalSet<T, Compare>()
```

空の区間集合を構築します。

**計算量**
- $O(1)$

---

## add_interval

```cpp
std::pair<T, T> add_interval(const T& L, const T& R)
std::pair<T, T> add_interval(const std::pair<T, T>& LR)
```

半開区間 `[L, R)` を追加し、必要に応じて既存の区間とマージします。  
戻り値は、追加後に `[L, R)` を含んでいる 1 つの大きな区間 `[l, r)` です。

**簡単な例**

- もともと `[1, 3) [5, 7)` がある状態で `add_interval(2, 6)` を呼ぶと、  
  区間は `[1, 7)` になります。


**制約**

- `L < R` または `LR.first < LR.second`

**計算量**

- 変更される区間数を $k$、全体の区間数を $M$ とすると  
  $O(k \log M)$

---

## erase_interval

```cpp
void erase_interval(const T& L, const T& R)
void erase_interval(const std::pair<T, T>& LR)
```

区間集合から半開区間 `[L, R)` を 集合として差し引きます。  
部分的に重なる区間は分割され、完全に含まれる区間は削除されます。

**簡単な例**

- もともと `[1, 3) [5, 8) [10, 13)` がある状態で  
  `erase_interval(2, 7)` を呼ぶと、  
  区間は `[1, 2) [7, 8) [10, 13)` になります。

**制約**

- `L < R` または `LR.first < LR.second`

**計算量**

- 変更される区間数を $k$、全体の区間数を $M$ とすると  
  $O(k \log M)$

---

## same

```cpp
bool same(T u, T v) const
```

`u` と `v` が同じ区間（同じ連結成分）に属するかを判定します。  
どちらか一方でもどの区間にも属していなければ `false` を返します。

**計算量**

- $O(\log M)$

---

## length

```cpp
T length(const T& u) const
```

`u` が属する区間 `[L, R)` の長さ `R - L` を返します。  
`u` がどの区間にも属していない場合は `0` を返します。  
`T` が整数型のときは、「区間に含まれる要素数」として扱えます。

**計算量**

- $O(\log M)$

---

## get_sum_lentgth

```cpp
T get_sum_lentgth() const
```

すべての区間長の合計を返します。

**計算量**

- $O(1)$

---

## print（デバッグ用途）

```cpp
void print() const
```

保持している区間を `[L, R)` 形式で標準出力に出力します。  

**計算量**

- 区間数を $M$ とすると $O(M)$
