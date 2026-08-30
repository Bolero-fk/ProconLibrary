---
title: 括弧列区間クエリ
documentation_of: //DataStructure/bracket_range_query.hpp
parent: Data Structure
---

# 括弧列区間クエリ

括弧列に対する区間クエリを処理するデータ構造です。

文字列の 1 点更新を行いながら、任意の区間について括弧の対応関係を取得できます。  
`'('` と `')'` 以外の文字は括弧列に寄与しません。

主に以下の操作を行えます。

- 文字列の 1 点更新
- 区間内で対応付けられる括弧ペア数の取得
- 区間内で対応先のない `'('` と `')'` の個数の取得
- 区間が正しい括弧列かの判定

以下、管理する文字列の長さを $N$ とします。

## S

```cpp
struct S
{
    int matched;
    int open;
    int close;
};
```

区間内の括弧の対応関係を表す構造体です。

各メンバは以下を表します。

- `matched` : 正しく対応付けられた括弧ペアの個数
- `open` : 対応先のない `'('` の個数
- `close` : 対応先のない `')'` の個数

## コンストラクタ

### デフォルトコンストラクタ

```cpp
BracketRangeQuery()
```

長さ $0$ の文字列で初期化します。

**計算量**

- $O(1)$

---

### 文字列から初期化

```cpp
explicit BracketRangeQuery(const string &s_)
```

文字列 `s_` で初期化します。

`'('` と `')'` 以外の文字は括弧列に寄与しません。

**計算量**

- $O(N)$

---

### 長さを指定して初期化

```cpp
explicit BracketRangeQuery(int n_)
```

長さ `n_` の文字列で初期化します。  
初期状態では、すべての文字が括弧列に寄与しない文字として扱われます。

**制約**

- $0 \leq N$

**計算量**

- $O(N)$

## set

```cpp
void set(int i, char c)
```

$i$ 文字目を `c` に変更します。

`c` が `'('` または `')'` 以外の場合、その文字は括弧列に寄与しません。

**制約**

- $0 \leq i < N$

**計算量**

- $O(\log N)$

## prod

```cpp
S prod(int l, int r)
```

区間 $[l, r)$ の括弧の対応関係を取得します。

戻り値の `matched` には区間内で正しく対応付けられる括弧ペアの最大数、`open` と `close` には対応先のない括弧の個数が格納されます。

**制約**

- $0 \leq l \leq r \leq N$

**計算量**

- $O(\log N)$

## is_valid

```cpp
bool is_valid(int l, int r)
```

区間 $[l, r)$ が正しい括弧列であるかを判定します。

`'('` と `')'` 以外の文字は無視されます。  
空区間は正しい括弧列として扱います。

**戻り値**

- 正しい括弧列なら `true`
- そうでなければ `false`

**制約**

- $0 \leq l \leq r \leq N$

**計算量**

- $O(\log N)$

## count_matched_pairs

```cpp
int count_matched_pairs(int l, int r)
```

区間 $[l, r)$ で、順序を保ったまま正しく対応付けられる括弧ペアの最大数を返します。

これは `prod(l, r).matched` と同じ値です。

**制約**

- $0 \leq l \leq r \leq N$

**計算量**

- $O(\log N)$

## str

```cpp
const string &str() const
```

現在保持している文字列を参照で返します。

**計算量**

- $O(1)$

## 関連情報

* [AtCoder Library `segtree`](https://atcoder.github.io/ac-library/production/document_ja/segtree.html): 依存クラス