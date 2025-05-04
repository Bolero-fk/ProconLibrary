---
title: 差分制約系 (牛ゲー)
documentation_of: //Math/difference_constraints_solver.hpp
parent: Math
nav_order: 1
---

# 差分制約系 (牛ゲー)

次のような差分制約

- $x_i - x_j \le c$
- $x_i - x_j \ge c$
- $x_i - x_j = c$

の集合をすべて満たすような変数 $x_i$ の値を求める問題を解きます。  
与えられた基準点 $S$ に対して $x_S = 0$ を仮定し、各 $x_i - x_S$ が**最大の値**となるような割り当てを計算します。  
いわゆる「牛ゲー」として知られる問題を解くことができます。

## コンストラクタ
```cpp
DifferenceConstraintsSolver<T> solver(int n)
```

変数 $x_0, x_1, \dots, x_{n-1}$ を持つ空の制約系を作成します。

**計算量**

- $O(N)$

## add_leq_constraint

```cpp
void dcs.add_leq_constraint(int i, int j, T c)
```

制約 $x_i - x_j \le c$ を追加します。

**制約**

- $0 \le i, j < N$

**計算量**

- $O(1)$

## add_geq_constraint

```cpp
void dcs.add_geq_constraint(int i, int j, T c)
```

制約 $x_i - x_j \ge c$ を追加します。

**制約**

- $0 \le i, j < N$

**計算量**

- $O(1)$

## add_eq_constraint

```cpp
void dcs.add_eq_constraint(int i, int j, T c)
```

制約 $x_i - x_j = c$ を追加します。

**制約**

- $0 \le i, j < N$

**計算量**

- $O(1)$

## solve

```cpp
pair<bool, vector<T>> solver.solve(int S = 0)
```

基準点 $x_S = 0$ を仮定し、すべての制約を満たす $x_i - x_S$ の最大の解を求めます。  
解が存在しない（矛盾がある）場合は `false` と空の配列を返します。

**制約**

- $0 \le S < N$

**計算量**

- $O(NM)$（$M$ は追加された制約の数）

## Tips

### 特定の差分の最小値を求めたい場合

このライブラリでは、`solve(S)` を使うことで各 $x_i - x_S$ の最大値を得ることができます。

一方、特定の二変数 $x_T - x_S$ の**最小値**を知りたい場合は、次のようにする：

```cpp
auto [ok, x] = solver.solve(T);
T min_value = -x[S];  
```

このように、`solve(T)[S]` の符号を反転することで、$x_T - x_S$ の最小値を求めることができます。
