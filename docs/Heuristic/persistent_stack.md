---
title: 永続スタック (生ポインタ)
documentation_of: //Heuristic/raw_pointer_persistent_stack.hpp
---

# 永続スタック (生ポインタ)
[永続スタック](../Heuristic/persistent_stack.md)のポインタに関する内部実装を生ポインタに変更したクラスです。  
ポインタの開放処理が速くなる半面、**メモリリークやダングリングポインタなどのリスクが生じる**ことを理解したうえで使用すること。  

## コンストラクタ
```cpp
RawPointerPersistentStack<T> ps
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
