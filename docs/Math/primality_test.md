---
title: 素数判定
documentation_of: //Math/primality_test.hpp
---

# PrimalityTest
Miller-Rabin素数判定法を用いた素数判定を行います。  
内部での累乗の計算を128ビット整数を用いた繰り返し二乗法で行っているため、やや速度が遅くなっています。    
モンゴメリ乗算をライブラリに追加したら累乗計算の部分は置き換えたい。  

## PrimalityTest::is_prime
```cpp
static bool PrimalityTest::is_prime(long long N)
```
整数`N`が素数であるかどうかを判定します。

**制約**
- $0 \leq N$

**計算量**
- $O(\log N)$
