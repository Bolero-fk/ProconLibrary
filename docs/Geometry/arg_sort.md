---
title: 偏角ソート
documentation_of: //Geometry/arg_sort.hpp
parent: Geometry
---

# 偏角ソート（整数演算）

2 次元ベクトル $(x, y)$ を偏角 $\theta = \mathrm{atan2}(y, x)$ の昇順（範囲 $(-\pi, \pi]$）でソートするための比較関数です。  
浮動小数点演算を使用せず、符号判定と外積（クロス積）だけで順序を定めます。

- 原点 $(0,0)$ は $\theta = 0$ とみなし、グループ `0` として扱います。
- 同じ偏角の点同士の順序は任意です（`cross == 0` のときは同値扱い）。

## 関数

```cpp
bool arg_comp(const pair<long long, long long> &p,
              const pair<long long, long long> &q)
```

`p` と `q` を偏角順（$(-\pi,\pi]$ の昇順）に比較し、`p` が `q` より先なら `true` を返します。

## 計算量

- 1 回の比較は $O(1)$
- ソート全体は $O(N \log N)$


## 参考

* [drken「Sort Points by Argument」解説](https://drken1215.hatenablog.com/entry/2023/08/27/223208)
