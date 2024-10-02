---
title: 高速素因数分解
documentation_of: //Math/fast_factorizer.hpp
---

# FastFactorizer
Pollard's rho アルゴリズムを用いた素因数分解を行います。
素数判定にはMiller-Rabin素数判定法を使用しています。

## FastFactorizer::factorize
```cpp
static vector<long long> FastFactorizer::factorize(long long N)
```
整数 `N` を素因数分解し、因数を昇順に並べたリストを返します。

**制約**
- $0 \lt N$

**計算量**
-  $O(\sqrt[4]{N})$
