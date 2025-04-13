---
title: 素数列挙
documentation_of: //Math/enumerate_primes.hpp
parent: Math
---

# enumerate_primes

```cpp
vector<long long> enumerate_primes(long long n)
```

エラトステネスの篩によって`n`以下の素数を計算し、返します。

**制約**

- $0 \lt n$

**計算量**

- $O(n \log \log n)$
