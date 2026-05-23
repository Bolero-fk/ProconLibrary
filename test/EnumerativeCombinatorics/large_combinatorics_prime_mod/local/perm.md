---
title: 順列 (nPr)
documentation_of: //test/EnumerativeCombinatorics/combination_prime_mod/local/perm.cpp
parent: Enumerative Combinatorics
nav_exclude: true
search_exclude: true
---

# 順列 (nPr)

## 問題文

$Q$ 個のクエリが与えられます。

各クエリでは、整数 $n, r$ が与えられるので、順列 $nPr$ を $998244353$ で割った余りを求めてください。

順列 $nPr$ は、$n$ 個の異なるものから $r$ 個を選んで並べる場合の数であり、次の式で表されます。

$$
nPr = \frac{n!}{(n-r)!}
$$

ただし、$r > n$ の場合は $0$ とします。

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

$i$ 行目には、$n_iPr_i$ を $998244353$ で割った余りを出力してください。

## 制約

* $1 \leq Q \leq 200000$
* $0 \leq n_i \leq 200000$
* $0 \leq r_i \leq 200000$
* 入力はすべて整数
