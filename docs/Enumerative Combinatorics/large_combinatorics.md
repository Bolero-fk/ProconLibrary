---
title: 組合せ・順列・重複組合せ (大きい n・素数 mod)
documentation_of: //EnumerativeCombinatorics/large_combinatorics.hpp
parent: Enumerative Combinatorics
---

# Large Combinatorics

`large_combinatorics` は、巨大な $n$ に対して順列・組合せ・重複組合せを素数 mod 上で計算するためのライブラリです。

通常の階乗前計算型の組合せライブラリとは異なり、$n$ ではなく $r$ に比例した時間で計算します。  
そのため、$n$ が非常に大きく、$r$ が比較的小さい場合に適しています。

このライブラリでは、以下の値を計算できます。

- 順列 $P(n, r)$
- 組合せ $C(n, r)$
- 重複組合せ $H(n, r)$

必要になった $r$ まで内部の前処理配列を自動で拡張するため、コンストラクタで上限を指定する必要はありません。

## コンストラクタ

```cpp
large_combinatorics()
```

空の `large_combinatorics` を作成します。  
前処理配列は、`C` または `H` が呼ばれたときに必要な範囲まで自動で拡張されます。

**計算量**
- $O(1)$

---

## P

```cpp
mint P(long long n, long long r)
```

順列 $P(n, r)$ を返します。

$$
P(n, r) = n(n - 1)(n - 2) \cdots (n - r + 1)
$$

$n < r$ の場合は `0` を返します。  
$n < 0$ または $r < 0$ の場合も `0` を返します。

**制約**
- `mint` は `mod()` を持つ modint 型であること
- 計算途中の `n - i` が `long long` の範囲に収まること

**計算量**
- $O(r)$

---

## C

```cpp
mint C(long long n, long long r)
```

組合せ $C(n, r)$ を返します。

$$
C(n, r) = \frac{n(n - 1)(n - 2) \cdots (n - r + 1)}{r!}
$$

$n < r$ の場合は `0` を返します。  
$n < 0$ または $r < 0$ の場合も `0` を返します。

必要に応じて、$r!$ の逆元を求めるための前処理配列を $r$ まで自動で拡張します。

**制約**
- `mint` は `mod()` を持つ modint 型であること
- $0 \leq r < \mathrm{mod}$
- 計算途中の `n - i` が `long long` の範囲に収まること

**計算量**
- $O(r)$
- ただし、これまでに処理した最大の $r$ を超える場合は、追加で前処理配列の拡張に $O(r)$

---

## H

```cpp
mint H(long long n, long long r)
```

重複組合せ $H(n, r)$ を返します。

$$
H(n, r) = C(n + r - 1, r)
$$

$n < 0$ または $r < 0$ の場合は `0` を返します。  
$n = 0$ の場合、$r = 0$ なら `1`、それ以外なら `0` を返します。

**制約**
- `mint` は `mod()` を持つ modint 型であること
- $0 \leq r < \mathrm{mod}$
- `n + r - 1` が `long long` の範囲に収まること
- 計算途中の値が `long long` の範囲に収まること

**計算量**
- $O(r)$
- ただし、これまでに処理した最大の $r$ を超える場合は、追加で前処理配列の拡張に $O(r)$