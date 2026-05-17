---
title: 組合せ・順列・重複組合せ (素数 mod)
documentation_of: //EnumerativeCombinatorics/combination_prime_mod.hpp
parent: Enumerative Combinatorics
---

# 組合せ・順列・重複組合せ (素数 mod)

組合せ $nCr$、順列 $nPr$、重複組合せ $nHr$ を素数 $m$ で割った余りとして計算できます。

階乗およびその逆元を前計算することで、各値を定数時間で取得できます。
テンプレート引数 `mint` には、`atcoder::modint` 系の型を指定することを前提としています。

## 参考

* [AtCoder解説放送ライブラリ集](https://github.com/atcoder/live_library/blob/master/comb.cpp)

## コンストラクタ

```cpp
combinatorics<mint>(int n)
```

$0$ 以上 $n$ 以下の階乗および階乗の逆元を前計算します。

これにより、任意の $0 \leq r \leq a \leq n$ に対して、組合せ $aCr$ および順列 $aPr$ を定数時間で計算できます。

また、重複組合せ $aHr$ は次の式を用いて計算されます。

$$
aHr = \binom{a + r - 1}{r}
$$

そのため、`H(a, r)` を呼び出す場合は、$a + r - 1 \leq n$ を満たすように前計算サイズを指定する必要があります。

### 制約

* $0 \leq n <$ `mint::mod()`

### 計算量

* $O(n)$

## メンバ関数

### operator()

```cpp
mint operator()(int n, int k)
```

二項係数 $\binom{n}{k}$ を法 $m$ で割った余りとして返します。

`C(n, k)` と同じ値を返します。

$n < 0$、$k < 0$、または $k > n$ の場合は $0$ を返します。

### 制約

* $0 \leq n \leq$ コンストラクタで指定した値

### 計算量

* $O(1)$

### C

```cpp
mint C(int n, int r)
```

組合せ $nCr$ を法 $m$ で割った余りとして返します。

$$
nCr = \frac{n!}{r!(n-r)!}
$$

$n < 0$、$r < 0$、または $r > n$ の場合は $0$ を返します。

### 制約

* $0 \leq n \leq$ コンストラクタで指定した値

### 計算量

* $O(1)$

### P

```cpp
mint P(int n, int r)
```

順列 $nPr$ を法 $m$ で割った余りとして返します。

$$
nPr = \frac{n!}{(n-r)!}
$$

$n < 0$、$r < 0$、または $r > n$ の場合は $0$ を返します。

### 制約

* $0 \leq n \leq$ コンストラクタで指定した値

### 計算量

* $O(1)$

### H

```cpp
mint H(int n, int r)
```

重複組合せ $nHr$ を法 $m$ で割った余りとして返します。

$$
nHr = \binom{n + r - 1}{r}
$$

$n$ 種類のものから重複を許して $r$ 個選ぶ場合の数を表します。

$n < 0$ または $r < 0$ の場合は $0$ を返します。
また、$n = 0$ の場合は、$r = 0$ のときのみ $1$ を返し、それ以外では $0$ を返します。

### 制約

* $0 \leq n$
* $0 \leq r$
* $n = 0$ または $n + r - 1 \leq$ コンストラクタで指定した値

### 計算量

* $O(1)$