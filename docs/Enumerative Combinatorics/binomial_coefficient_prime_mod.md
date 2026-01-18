---
title: 二項係数 (素数 mod)
documentation_of: //EnumerativeCombinatorics/binomial_coefficient_prime_mod.hpp
parent: Enumerative Combinatorics
---

# 二項係数 (素数 mod)

二項係数 $nCk = \frac{n!}{k!(n-k)!}$ を素数 $m$ で割った余りが計算できます。

## 参考
* [AtCoder解説放送ライブラリ集](https://github.com/atcoder/live_library/blob/master/comb.cpp)

## コンストラクタ

```cpp
combination<mint>(int n)
```

二項係数 $aCb$ を高速に計算するためのクラスです。
階乗およびその逆元を事前に前計算し、任意の $0 \leq b \leq a \leq n$ に対して定数時間で値を取得できます。
テンプレート引数 `mint` には、`atcoder::modint` 系の型を指定することを前提としています。

### 制約
* $0 \le n <$ `mint::mod()`

### 計算量
* : $O(n)$

## メンバ関数
```cpp
mint operator()(int n, int k)
```

二項係数 $\binom{n}{k}$ を法 $m$ で割った余りとして返します。

### 計算量
* $O(1)$
