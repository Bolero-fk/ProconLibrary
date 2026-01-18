---
title: 括弧列区間クエリ
documentation_of: //DataStructure/bracket_range_query.hpp
parent: Data Structure
nav_order: 7
---

# 括弧列区間クエリ

文字列に対して1点更新と区間が正しい括弧列として成立するかの判定を行うデータ構造です。  
判定では `'('` と `')'` 以外の文字は無視します。

- `set(i, c)` : `i` 文字目を `c` に変更
- `is_valid(l, r)` : 区間 `[l, r)` の部分文字列から `'('` と `')'` だけを抜き出した列が、正しい括弧列か判定

## コンストラクタ

```cpp
BracketRangeQuery(const std::string& s)
```

初期文字列 `s` で初期化します。

**制約**
- `s` は任意の文字列でよい（ただし判定に寄与するのは `'('` と `')'` のみ）

**計算量**
- $O(\|s\|)$

---

```cpp
BracketRangeQuery(int N)
```

長さ `N` の文字列で初期化します。初期状態はすべて「括弧以外」（寄与 0）として扱います。

**制約**
- $0 \leq N$

**計算量**
- $O(N)$

---

## set

```cpp
void set(int i, char c)
```

`i` 文字目（0-indexed）を `c` に変更します。  
`c` が `'('` / `')'` 以外の場合は、判定上は「無視される文字」として扱われます。

**制約**
- `0 ≤ i < N`
- `c` は任意の文字でよい（ただし判定に寄与するのは `'('` と `')'` のみ）

**計算量**
- $O(\log N)$

---

## is_valid

```cpp
bool is_valid(int l, int r)
```

区間 `[l, r)`（0-indexed）の部分文字列から `'('` と `')'` のみを抜き出した列が、正しい括弧列であるか判定します。  
空区間（`l == r`）は常に `true` を返します。

**戻り値**
- 正しい括弧列なら `true`
- そうでなければ `false`

**制約**
- `0 ≤ l ≤ r ≤ N`

**計算量**
- $O(\log N)$

---

## str（デバッグ用）

```cpp
const std::string& str() const
```

内部に保持している現在の文字列を参照で返します（デバッグ用途を想定）。

**計算量**
- $O(1)$

## 関連情報

- [AtCoder Library `lazysegtree`](https://atcoder.github.io/ac-library/production/document_ja/lazysegtree.html): 依存クラス
