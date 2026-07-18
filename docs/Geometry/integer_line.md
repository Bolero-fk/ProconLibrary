---
title: 整数直線
documentation_of: //Geometry/integer_line.hpp
parent: Geometry
---

# 整数直線

`IntegerLine` は、整数係数の直線

$$
Ax + By + C = 0
$$

を表す構造体です。

座標と係数には `__int128_t` を使用し、浮動小数点数の誤差を発生させずに直線の位置関係を判定します。

構築時に係数を最大公約数で割り、最初の非零係数が正になるように符号を統一します。  
そのため、同じ直線は常に同じ係数で表されます。

主に以下の操作を提供します。

- 異なる 2 点を通る直線の構築
- 2 点の垂直二等分線の構築
- 点が直線上にあるかの判定
- 2 点が直線の同じ側または反対側にあるかの判定
- 2 直線の平行・一致・垂直判定
- 2 直線の交点の厳密な計算

## Point

```cpp
using Point = std::pair<__int128_t, __int128_t>;
```

整数座標の点を表します。

- `first`: $x$ 座標
- `second`: $y$ 座標

## Intersection

```cpp
using Intersection = std::array<__int128_t, 3>;
```

2 直線の交点を、分数のまま厳密に表します。

値を `{x_numerator, y_numerator, denominator}` とすると、交点は次の座標です。

$$
\left(
\frac{x_{\mathrm{numerator}}}{\mathrm{denominator}},
\frac{y_{\mathrm{numerator}}}{\mathrm{denominator}}
\right)
$$

分母は正の値に統一されます。  
分子と分母は約分されるとは限りません。

---

## コンストラクタ

```cpp
IntegerLine(__int128_t A, __int128_t B, __int128_t C)
```

直線

$$
Ax + By + C = 0
$$

を構築します。

構築時に、以下の正規化を行います。

1. $\gcd(\lvert A\rvert,\lvert B\rvert,\lvert C\rvert)$ で各係数を割る
2. `A < 0`、または `A == 0 && B < 0` の場合は、すべての係数の符号を反転する

これにより、同じ直線は常に同じ係数で表されます。

**制約**
- `A` と `B` が同時に $0$ でないこと
- 計算結果が `__int128_t` の範囲に収まること

**計算量**
- $O(\log M)$
- $M=\max(\lvert A\rvert,\lvert B\rvert,\lvert C\rvert)$

---

## through

```cpp
static IntegerLine through(Point p, Point q)
```

異なる 2 点 `p`, `q` を通る直線を返します。

戻り値の係数は正規化されます。

**制約**
- `p != q`
- 計算結果が `__int128_t` の範囲に収まること

**計算量**
- $O(\log M)$
- $M$ は構築される直線の係数の絶対値の最大値

---

## perpendicular_bisector

```cpp
static IntegerLine perpendicular_bisector(Point p, Point q)
```

異なる 2 点 `p`, `q` を結ぶ線分の垂直二等分線を返します。

戻り値の係数は正規化されます。

**制約**
- `p != q`
- 座標の二乗を含む計算結果が `__int128_t` の範囲に収まること

**計算量**
- $O(\log M)$
- $M$ は構築される直線の係数の絶対値の最大値

---

## eval

```cpp
__int128_t eval(Point p) const
```

点 `p` の座標を直線方程式の左辺

$$
Ax + By + C
$$

へ代入した値を返します。

戻り値が $0$ なら、`p` は直線上にあります。  
戻り値の符号を比較することで、複数の点が直線のどちら側にあるかを判定できます。

係数の符号は正規化されているため、同じ直線から生成された `IntegerLine` では戻り値の符号も一意に定まります。

**制約**
- 計算結果が `__int128_t` の範囲に収まること

**計算量**
- $O(1)$

---

## contains

```cpp
bool contains(Point p) const
```

点 `p` が直線上にある場合は `true`、それ以外の場合は `false` を返します。

**制約**
- 計算結果が `__int128_t` の範囲に収まること

**計算量**
- $O(1)$

---

## same_side

```cpp
bool same_side(Point p, Point q) const
```

点 `p`, `q` が直線の同じ側にある場合は `true` を返します。

どちらか一方でも直線上にある場合は `false` を返します。

**制約**
- 計算結果が `__int128_t` の範囲に収まること

**計算量**
- $O(1)$

---

## opposite_side

```cpp
bool opposite_side(Point p, Point q) const
```

点 `p`, `q` が直線の反対側にある場合は `true` を返します。

どちらか一方でも直線上にある場合は `false` を返します。

**制約**
- 計算結果が `__int128_t` の範囲に収まること

**計算量**
- $O(1)$

---

## is_parallel

```cpp
bool is_parallel(const IntegerLine& other) const
```

この直線と `other` が平行である場合は `true` を返します。

同一直線も平行として扱います。

**制約**
- 係数同士の積が `__int128_t` の範囲に収まること

**計算量**
- $O(1)$

---

## is_same

```cpp
bool is_same(const IntegerLine& other) const
```

この直線と `other` が同一直線を表す場合は `true` を返します。

各直線の係数は構築時に正規化されるため、正規化後の係数が一致するかを判定します。

**計算量**
- $O(1)$

---

## is_perpendicular

```cpp
bool is_perpendicular(const IntegerLine& other) const
```

この直線と `other` が垂直である場合は `true` を返します。

**制約**
- 係数同士の積および和が `__int128_t` の範囲に収まること

**計算量**
- $O(1)$

---

## intersection

```cpp
std::optional<Intersection> intersection(const IntegerLine& other) const
```

この直線と `other` の交点を返します。

交点が一意に存在する場合、戻り値は次の形式です。

```cpp
{xの分子, yの分子, 共通分母}
```

実際の交点は次の座標です。

$$
\left(
\frac{\text{xの分子}}{\text{共通分母}},
\frac{\text{yの分子}}{\text{共通分母}}
\right)
$$

2 直線が平行または同一直線であり、一意な交点を持たない場合は `std::nullopt` を返します。

分母は正の値に統一されますが、分子と分母は約分されるとは限りません。

**制約**
- 係数同士の積および差が `__int128_t` の範囲に収まること

**計算量**
- $O(1)$