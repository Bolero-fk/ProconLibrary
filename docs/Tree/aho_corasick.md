---
title: Aho-Corasick
documentation_of: //Tree/aho_corasick.hpp
parent: Tree
---

# Aho-Corasick

Aho-Corasick は、複数のパターン列をまとめて扱うためのオートマトンです。  
Trie に suffix link を追加することで、現在までに読んだ列の末尾が、登録済みパターンのどの接頭辞に一致しているかを状態として管理できます。

このライブラリでは、`T` 型の値からなるパターン列を登録し、列を先頭から順に読んだときに、いずれかのパターンが末尾に出現しているかを判定できます。  
文字列に対して使う場合は `AhoCorasick<char>` として利用できます。

主に以下の用途に使えます。

- 複数パターンの文字列検索
- 禁止パターンを含まない列の数え上げ
- Trie 上の suffix link の構築
- パターン集合に対する状態遷移オートマトンの構築

## コンストラクタ

```cpp
AhoCorasick()
```

空の Aho-Corasick オートマトンを作成します。  
初期状態では、内部の Trie は root ノードのみを持ちます。

**計算量**
- $O(1)$

---

## insert

```cpp
template <typename Container>
int insert(const Container& pattern)
```

パターン列 `pattern` を追加します。  
戻り値として、`pattern` に対応する終端ノード ID を返します。

`Container::value_type` は `T` と一致している必要があります。

`insert` を呼び出した後は、再度 `build()` を呼ぶ必要があります。

**制約**
- `Container::value_type` が `T` と一致すること
- `T` は `unordered_map<T, int>` のキーとして利用できること

**計算量**
- $O(|pattern|)$ 期待時間

---

## build

```cpp
void build()
```

登録済みパターンから suffix link とマッチ情報を構築します。

各ノード `v` に対して、`suffix_link[v]` は `v` に対応する列の真の接尾辞のうち、Trie に存在する最長のものに対応するノード ID です。  
また、`matched[v]` は、状態 `v` に到達した時点で、いずれかの登録済みパターンが末尾に出現しているかを表します。

`move`、`is_matched`、`get_suffix_link` を使う前に、この関数を呼ぶ必要があります。

**計算量**
- $O(M \alpha)$ 期待時間

ここで、`M` は Trie のノード数、`\alpha` は各ノードから出ている遷移数の合計に対する走査量です。  
実装上は、Trie に存在する辺を BFS で 1 回ずつ処理します。

---

## move

```cpp
int move(int node_id, const T& value) const
```

現在状態 `node_id` から値 `value` を 1 つ読んだ後の状態を返します。

直接の遷移が存在しない場合は suffix link をたどり、遷移可能な最長の接尾辞状態へ移動します。  
どの状態からも遷移できない場合は root に戻ります。

**制約**
- `build()` が呼ばれていること
- $0 \leq node_id < size()$

**計算量**
- 最悪 $O(\text{状態の深さ})$ 期待時間

---

## is_matched

```cpp
bool is_matched(int node_id) const
```

状態 `node_id` に到達した時点で、いずれかの登録済みパターンが末尾に出現しているかを返します。

例えば、パターンとして `"bc"` が登録されている場合、現在までに読んだ文字列の末尾が `"bc"` であれば `true` を返します。  
また、現在状態そのものがパターン終端でなくても、suffix link をたどった先にパターン終端がある場合は `true` になります。

**制約**
- `build()` が呼ばれていること
- $0 \leq node_id < size()$

**計算量**
- $O(1)$

---

## get_suffix_link

```cpp
int get_suffix_link(int node_id) const
```

状態 `node_id` の suffix link 先のノード ID を返します。

suffix link は、現在ノードに対応する列の真の接尾辞のうち、Trie に存在する最長のものを表します。

**制約**
- `build()` が呼ばれていること
- $0 \leq node_id < size()$

**計算量**
- $O(1)$

---

## parent

```cpp
int parent(int node_id) const
```

Trie 上での親ノード ID を返します。  
root の `parent` は `-1` です。

**制約**
- $0 \leq node_id < size()$

**計算量**
- $O(1)$

---

## transition_value

```cpp
T transition_value(int node_id) const
```

Trie 上で、親ノードから `node_id` へ遷移するときに使った値を返します。  
root では意味を持ちません。

**制約**
- $0 \leq node_id < size()$

**計算量**
- $O(1)$

---

## size

```cpp
int size() const
```

内部の Trie のノード数を返します。

**計算量**
- $O(1)$