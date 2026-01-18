---
title: 永続スタック
documentation_of: //DataStructure/persistent_stack.hpp
parent: Data Structure
---

# 永続スタック
永続スタックは、永続データ構造の一種で、変更の履歴だけを持つことでデータ自体のサイズを小さく保ちながら `stack` の操作を実現できます。このデータ構造は、最新の変更だけをコピーするので過去の状態を効率的に保存することが可能です。

## 参考
- [あなたの庭に永続データ構造を飾りませんか？](https://noshi91.hatenablog.com/entry/2019/02/04/175100)
- [Persistent Stack - AtCoder Heuristic Contest Memo](https://jetbead.github.io/AtCoderHeuristicContestMemo/Library/persistent_stack.html)

## コンストラクタ
```cpp
PersistentStack<T> ps
```
- 型 `T` を要素に持つ空のスタックを作成します。

**計算量**

- $O(1)$

## push

```cpp
void ps.push(const T &v)
```

要素 `v` をスタックに追加します。

**計算量**

- $O(1)$

## pop

```cpp
void ps.pop()
```

スタックの先頭の要素を削除します。

**制約**

- スタックが空でないこと。

**計算量**

- $O(1)$

## top

```cpp
T ps.top()
```
スタックの先頭の要素を返します。

**制約**

- スタックが空でないこと。

**計算量**

- $O(1)$

## empty

```cpp
bool ps.empty()
```

スタックが空かどうかを返します。

**計算量**

- $O(1)$

## size

```cpp
int ps.size()
```

スタックに含まれる要素の数を返します。

**計算量**

- $O(1)$

## extract_values

```cpp
vector<T> ps.extract_values()
```

スタックのすべての要素を順番に取り出し、`vector` に格納して返します。  
スタックの順番は保持され、最初に追加した要素が最初に、最後に追加した要素が最後に配置されます。

**計算量**

- $O(n)$
