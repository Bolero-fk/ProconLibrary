---
title: k乗根（整数）
documentation_of: //Math/kth_root_integer.hpp
---

# kth_root

```cpp
T kth_root(T a, T k)
```

入力された値の$\operatorname{floor}\left( \sqrt[k]{a} \right)$を返します。

**制約**
- 型`T`は整数型
- $0 \leq a$
- $0 \lt k$

**計算量**

- $O(k \log a)$
