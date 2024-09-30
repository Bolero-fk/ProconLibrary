---
title: 整数累乗 (mod)
documentation_of: //Math/mod_power.hpp
---

# prime_factorize

```cpp
T  mod_pow(T x, T n, T mod)
```

繰り返し二乗法により`mod`を法としたときの`x^n`を計算して返します。

**制約**
$ 0 \leq n$
$ 0 < \text{mod}$
$ \text{mod}^2 \leq \text{型Tの最大値}$

**計算量**
- $O(\log n)$
