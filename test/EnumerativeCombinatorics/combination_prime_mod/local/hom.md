---
title: 重複組合せ (nHr)
documentation_of: //test/EnumerativeCombinatorics/combination_prime_mod/local/hom.cpp
parent: Enumerative Combinatorics
nav_exclude: true
search_exclude: true
---

# 重複組合せ (nHr)

## 問題文

$Q$ 個のクエリが与えられます。

各クエリでは、整数 $n, r$ が与えられるので、重複組合せ $nHr$ を $998244353$ で割った余りを求めてください。

重複組合せ $nHr$ は、$n$ 種類のものから重複を許して $r$ 個選ぶ場合の数であり、次の式で表されます。

$$
nHr = \binom{n + r - 1}{r}
$$

ただし、$n = 0$ の場合は、$r = 0$ のときのみ $1$ とし、それ以外では $0$ とします。

## 入力

```text
Q
n_1 r_1
n_2 r_2
...
n_Q r_Q
```

## 出力

$Q$ 行出力してください。

$i$ 行目には、$n_iHr_i$ を $998244353$ で割った余りを出力してください。

## 制約

* $1 \leq Q \leq 200000$
* $0 \leq n_i \leq 200000$
* $0 \leq r_i \leq 200000$
* $n_i + r_i - 1 \leq 200000$
  * ただし、$n_i = 0$ の場合を除く
* 入力はすべて整数
