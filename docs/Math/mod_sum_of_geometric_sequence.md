---
title: 等比数列の総和 (mod)
documentation_of: //Math/mod_sum_of_geometric_sequence.hpp
parent: Math
---

# sum_of_geometric_sequence

```cpp
mint sum_of_geometric_sequence(mint a, mint r, long long n)
```

初項$a$、公比$r$、項数$n$からなる等比数列の部分和 $\sum_{i=0}^{n-1} a \cdot r^i$ を計算し、その値を返します。

**制約**
- $0 < n$

**計算量**

- $O(\log n)$
