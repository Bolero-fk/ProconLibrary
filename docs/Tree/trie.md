---
title: Trie
documentation_of: //Tree/trie.hpp
parent: Tree
---

# Trie

Trie は、複数の列を木構造として管理するデータ構造です。  
各辺に値を対応させ、root からあるノードまでの経路が 1 つの列の接頭辞を表します。

このライブラリでは、`T` 型の値からなる列を追加し、接頭辞に対応するノードをたどることができます。  
文字列に対して使う場合は `Trie<char>` として利用できます。

主に以下の用途に使えます。

- 複数の文字列や列の接頭辞を管理する
- ある列の接頭辞が Trie 上に存在するかを順に調べる
- 挿入した列に対応する終端ノード ID を取得する
- ある接頭辞以下の部分木を削除する

## Node

```cpp
struct Node
```

Trie の各ノードを表す構造体です。

各ノードは以下の情報を持ちます。

- 子ノードへの遷移
- 親ノードの ID
- 親からこのノードへ遷移するときに使った値
- このノードを通過する列の個数
- このノードで終端する列の個数

---

## コンストラクタ

```cpp
Trie()
```

空の Trie を作成します。  
初期状態では、root ノードのみを持ちます。

**計算量**
- $O(1)$

---

## insert

```cpp
template <typename Container>
int insert(const Container& v)
```

列 `v` を Trie に追加します。  
戻り値として、`v` に対応する終端ノード ID を返します。

`Container::value_type` は `T` と一致している必要があります。

**制約**
- `Container::value_type` が `T` と一致すること
- `T` は `unordered_map<T, int>` のキーとして利用できること

**計算量**
- $O(|v|)$ 期待時間

---

## iterate_prefix

```cpp
template <typename Container, typename Func>
void iterate_prefix(const Container& v, Func f)
```

列 `v` の接頭辞に対応するノードを順にたどり、それぞれのノードに対して `f` を実行します。

`f` は次の形式で呼び出されます。

```cpp
f(node_id, is_last)
```

- `node_id`：現在の接頭辞に対応するノード ID
- `is_last`：現在の接頭辞が `v` 全体と一致するかどうか

途中で対応する遷移が存在しなくなった場合、その時点で処理を終了します。

**制約**
- `Container::value_type` が `T` と一致すること
- `Func` が `f(int, bool)` として呼び出せること

**計算量**
- $O(|v|)$ 期待時間

---

## erase_subtrie

```cpp
template <typename Container>
void erase_subtrie(const Container& prefix)
```

`prefix` に対応するノード以下の部分木を論理的に削除します。

具体的には、`prefix` に対応するノードについて、

```cpp
pass_count = 0
end_count = 0
next_node_ids.clear()
```

を行います。  
また、祖先ノードの `pass_count` から、削除した部分木の `pass_count` を引きます。

`prefix` が Trie に存在しない場合は何もしません。

この関数は、`nodes` 配列からノード自体を削除するわけではありません。  
そのため、削除後も過去に作成されたノード ID が再利用されることはありません。

**制約**
- `Container::value_type` が `T` と一致すること

**計算量**
- $O(|prefix|)$ 期待時間