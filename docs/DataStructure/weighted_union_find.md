---
title: 重み付きUnion Find
documentation_of: //DataStructure/weighted_union_find.hpp
---


# 重み付きUnion Find
無向グラフに対して、

- 辺の追加
- $2$ 頂点が連結かの判定
- $2$ 頂点間の重み差の計算

をならし $O(\alpha(n))$ 時間で処理することが出来ます。

また、内部的に各連結成分ごとに代表となる頂点を $1$ つ持っています。辺の追加により連結成分がマージされる時、新たな代表元は元の連結成分の代表元のうちどちらかになります。

## コンストラクタ

```cpp
WeightedUnionFind<T> wuf(int n)
```

- 型`T` 型`T`の重みをもった頂点を作ります。
- $n$ 頂点 $0$ 辺の無向グラフを作ります。

**計算量**

- $O(n)$

## merge

```cpp
int wuf.merge(int a, int b, T w)
```

頂点$a$と頂点$b$の重みの差を$w$に設定します。
$a, b$ が連結だった場合はその代表元、非連結だった場合は新たな代表元を返します。

**制約**

- $0 \leq a < n$
- $0 \leq b < n$
- $ a $と$ b $が連結の場合、$weight(a) + w = weight(b)$

**計算量**

- ならし $O(\alpha(n))$

## same

```cpp
bool wuf.same(int a, int b)
```

頂点 $a, b$ が連結かどうかを返します。

**制約**

- $0 \leq a < n$
- $0 \leq b < n$

**計算量**

- ならし $O(\alpha(n))$

## leader

```cpp
int wuf.leader(int a)
```

頂点 $a$ の属する連結成分の代表元を返します。

**制約**

- $0 \leq a < n$

**計算量**

- ならし $O(\alpha(n))$

## size

```cpp
int wuf.size(int a)
```

頂点 $a$ の属する連結成分のサイズを返します。

**制約**

- $0 \leq a < n$

**計算量**

- ならし $O(\alpha(n))$

## weight

```cpp
T wuf.weight(int a)
```

頂点 $a$ とその代表元との重みの差を返します。

**制約**

- $0 \leq a < n$

**計算量**

- ならし $O(\alpha(n))$

## weight

```cpp
T wuf.diff(int a, int b)
```

頂点$a$と頂点$b$の重みの差を返します。

**制約**

- $0 \leq a < n$
- $0 \leq b < n$
- $a$ と $b$は連結

**計算量**

- ならし $O(\alpha(n))$

## groups

```cpp
vector<vector<int>> wuf.groups()
```

グラフを連結成分に分け、その情報を返します。

返り値は「「一つの連結成分の頂点番号のリスト」のリスト」です。
(内側外側限らず)vector内でどの順番で頂点が格納されているかは未定義です。

**計算量**

- $O(n)$
