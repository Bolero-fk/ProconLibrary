---
title: 素因数分解
documentation_of: //Math/prime_factorize.hpp
---

# prime_factorize

```cpp
vector<pair<long long, long long>> prime_factorize(long long N)
```

入力された整数`N`を素因数分解し、その結果を`vector<pair<long long, long long>>`として返します。  
各ペアは、最初の要素が素因数、2番目の要素がその素因数の指数を示します。

**制約**
- $1 \leq N$

**計算量**
- $O(\sqrt{N})$
