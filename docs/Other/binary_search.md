---
title: 二分探索
documentation_of: //Other/binary_search.hpp
parent: Other
---

# 二分探索

めぐる式二分探索により、与えられた条件を満たす境界値を求める関数です。
条件関数 `check` は単調性を仮定しています。

## bin_search (integer)
```cpp
template <typename T>
enable_if_t<is_integral_v<T>, T>
bin_search(T ok, T ng, function<bool(T)> check)
```

区間 `[ok, ng)` もしくは `(ng, ok]` において、

- `check(ok) = true`

- `check(ng) = false`

を満たす初期値を与えると、最終的に以下を満たす境界値を返します。

- 戻り値 `ret` は常に条件を満たします (`check(ret) = true`)。

- 隣の値 `ret + 1` または `ret - 1` は常に条件を満たしません (`check(ret ± 1) = false`)。

**計算量**

- $O(\log \mid ok - ng \mid)$

## bin_search (float)
```cpp
template <typename T>
enable_if_t<is_floating_point_v<T>, T>
bin_search(T ok, T ng, function<bool(T)> check, T precision = 1e-9)
```

区間 `[ok, ng)` または `(ng, ok]` において、浮動小数点数の探索を行います。
最終的に以下を満たす境界値 n を返します。

- `check(n) = true`, `check(n + precision) = false`

もしくは
- `check(n - precision) = false`, `check(n) = true`

つまり、条件が変化する境界を精度 `precision` 内で判定します。

**計算量**

- $O\left(\log\left(\frac{\mid ok - ng\mid}{\text{precision}}\right)\right)$
