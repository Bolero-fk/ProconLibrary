---
title: 繰り返し二乗法
documentation_of: //Other/fast_power.hpp
---

# 繰り返し二乗法

`x`の`n`乗を、繰り返し二乗法を用いて高速に計算する関数です。

## fast_pow
```cpp
template <class S>
S fast_pow(S x, long long n, function<S(S, S)> mul, function<S()> e)
```

- `x`: 底となる元
- `n`: 指数（非負整数）
- `mul`: 乗算を定義する二項演算（結合則 `mul(a, mul(b, c)) = mul(mul(a, b), c)` を満たす必要あり）
- `e`: 乗算の単位元(`mul(a, e) = a`)を返す関数

モノイド `(S, mul)` において、`x` の `n` 乗を計算します。

**制約**
- $0 \leq n$

**計算量**
- $O(\log n)$
