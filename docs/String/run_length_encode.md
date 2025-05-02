---
title: ランレングス圧縮
documentation_of: //String/run_length_encode.hpp
parent: String
nav_order: 1
---

# ランレングス圧縮

連続する同じ要素をまとめて、要素とその出現回数のペア列に変換します。

## run_length_encode
```cpp
template <typename Container>
vector<pair<typename Container::value_type, int>> run_length_encode(const Container &v)
```

連続する同一要素を1つのペアにまとめ、元のコンテナを走査して圧縮されたペア列を返します。


## 計算量
* $O(n)$
