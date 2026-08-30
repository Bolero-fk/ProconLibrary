---
title: 括弧列区間クエリ
documentation_of: //DataStructure/bracket_range_query.hpp
parent: Data Structure
---

# 括弧列区間クエリ

文字列に対して、1点更新・正しい括弧列かの判定・正しく対応付けられる括弧ペア数の取得を行うデータ構造です。
判定・カウントでは `'('` と `')'` 以外の文字は無視します。

内部ではセグメント木を使用し、各区間について以下の情報を管理します。

* 対応付けられた括弧ペア数
* 対応先のない `'('` の個数
* 対応先のない `')'` の個数

左右の区間を結合するとき、左区間の余った `'('` と右区間の余った `')'` を可能な限り対応付けます。

* `set(i, c)` : `i` 文字目を `c` に変更
* `is_valid(l, r)` : 区間 `[l, r)` が正しい括弧列か判定
* `count_matched_pairs(l, r)` : 区間 `[l, r)` で正しく対応付けられる括弧ペアの最大数を取得

## コンストラクタ

```cpp
BracketRangeQuery(const std::string& s)
```

初期文字列 `s` で初期化します。

**制約**

* `s` は任意の文字列でよい（ただし処理に寄与するのは `'('` と `')'` のみ）

**計算量**

* $O(|s|)$

---

```cpp
BracketRangeQuery(int N)
```

長さ `N` の文字列で初期化します。初期状態はすべて「括弧以外」（寄与 0）として扱います。

**制約**

* $0 \leq N$

**計算量**

* $O(N)$

---

## set

```cpp
void set(int i, char c)
```

`i` 文字目（0-indexed）を `c` に変更します。
`c` が `'('` / `')'` 以外の場合は、「無視される文字」として扱われます。

**制約**

* `0 ≤ i < N`

**計算量**

* $O(\log N)$

---

## is_valid

```cpp
bool is_valid(int l, int r)
```

区間 `[l, r)`（0-indexed）の部分文字列から `'('` と `')'` のみを抜き出した列が、正しい括弧列であるか判定します。

区間内で対応先のない `'('` と `')'` がともに 0 個なら、正しい括弧列です。

空区間（`l == r`）は常に `true` を返します。

**戻り値**

* 正しい括弧列なら `true`
* そうでなければ `false`

**制約**

* `0 ≤ l ≤ r ≤ N`

**計算量**

* $O(\log N)$

---

## count_matched_pairs

```cpp
int count_matched_pairs(int l, int r)
```

区間 `[l, r)`（0-indexed）で、順序を保ったまま正しく対応付けられる `'('` と `')'` のペア数の最大値を返します。

例えば、

```text
"()"   -> 1
"(())" -> 2
"()()" -> 2
"(()"  -> 1
")("   -> 0
```

となります。

**制約**

* `0 ≤ l ≤ r ≤ N`

**計算量**

* $O(\log N)$

---

## str（デバッグ用）

```cpp
const std::string& str() const
```

内部に保持している現在の文字列を参照で返します（デバッグ用途を想定）。

**計算量**

* $O(1)$

## 関連情報

* [AtCoder Library `segtree`](https://atcoder.github.io/ac-library/production/document_ja/segtree.html): 依存クラス
