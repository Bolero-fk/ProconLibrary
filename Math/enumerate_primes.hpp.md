---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/library_checker/Math/enumerate_primes.test.cpp
    title: test/library_checker/Math/enumerate_primes.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u30A8\u30E9\u30C8\u30B9\u30C6\u30CD\u30B9\u306E\u7BE9\u306B\u3088\
      \u308B\u7D20\u6570\u5217\u6319"
    links: []
  bundledCode: "#line 1 \"Math/enumerate_primes.hpp\"\n#include <bits/stdc++.h>\n\
    using namespace std;\n\n/// @brief \u30A8\u30E9\u30C8\u30B9\u30C6\u30CD\u30B9\u306E\
    \u7BE9\u306B\u3088\u308B\u7D20\u6570\u5217\u6319\nstruct PrimesEnumerator\n{\n\
    \    using ll = long long;\n    using P = pair<int, int>;\n    int N;\n\n    ///\
    \ @brief primes:=N\u4EE5\u4E0B\u306E\u7D20\u6570\n    vector<int> primes;\n\n\
    \    /** @brief \u5165\u529B\u3055\u308C\u305F\u5024\u4EE5\u4E0B\u306E\u5024\u304C\
    \u7D20\u6570\u304B\u3069\u3046\u304B\u3092\u5224\u5B9A\u3067\u304D\u308B\u30AF\
    \u30E9\u30B9\n     * @param N \u7D20\u6570\u304B\u3069\u3046\u304B\u3092\u5224\
    \u5B9A\u3057\u305F\u3044\u5024\u306E\u6700\u5927\u5024\n     * @note \u8A08\u7B97\
    \u91CF O(NloglogN)\n     */\n    PrimesEnumerator(int N = 1) : N(N)\n    {\n \
    \       vector<bool> isChecked(N + 1);\n        isChecked[0] = isChecked[1] =\
    \ true;\n        for (ll i = 2; i <= N; ++i)\n        {\n            if (isChecked[i])\n\
    \                continue;\n            primes.push_back(i);\n            isChecked[i]\
    \ = true;\n            for (ll j = i * i; j <= N; j += i)\n            {\n   \
    \             if (!isChecked[j])\n                    isChecked[j] = i;\n    \
    \        }\n        }\n    }\n};\n"
  code: "#include <bits/stdc++.h>\nusing namespace std;\n\n/// @brief \u30A8\u30E9\
    \u30C8\u30B9\u30C6\u30CD\u30B9\u306E\u7BE9\u306B\u3088\u308B\u7D20\u6570\u5217\
    \u6319\nstruct PrimesEnumerator\n{\n    using ll = long long;\n    using P = pair<int,\
    \ int>;\n    int N;\n\n    /// @brief primes:=N\u4EE5\u4E0B\u306E\u7D20\u6570\n\
    \    vector<int> primes;\n\n    /** @brief \u5165\u529B\u3055\u308C\u305F\u5024\
    \u4EE5\u4E0B\u306E\u5024\u304C\u7D20\u6570\u304B\u3069\u3046\u304B\u3092\u5224\
    \u5B9A\u3067\u304D\u308B\u30AF\u30E9\u30B9\n     * @param N \u7D20\u6570\u304B\
    \u3069\u3046\u304B\u3092\u5224\u5B9A\u3057\u305F\u3044\u5024\u306E\u6700\u5927\
    \u5024\n     * @note \u8A08\u7B97\u91CF O(NloglogN)\n     */\n    PrimesEnumerator(int\
    \ N = 1) : N(N)\n    {\n        vector<bool> isChecked(N + 1);\n        isChecked[0]\
    \ = isChecked[1] = true;\n        for (ll i = 2; i <= N; ++i)\n        {\n   \
    \         if (isChecked[i])\n                continue;\n            primes.push_back(i);\n\
    \            isChecked[i] = true;\n            for (ll j = i * i; j <= N; j +=\
    \ i)\n            {\n                if (!isChecked[j])\n                    isChecked[j]\
    \ = i;\n            }\n        }\n    }\n};"
  dependsOn: []
  isVerificationFile: false
  path: Math/enumerate_primes.hpp
  requiredBy: []
  timestamp: '2023-11-30 00:57:41+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/library_checker/Math/enumerate_primes.test.cpp
documentation_of: Math/enumerate_primes.hpp
layout: document
redirect_from:
- /library/Math/enumerate_primes.hpp
- /library/Math/enumerate_primes.hpp.html
title: "\u30A8\u30E9\u30C8\u30B9\u30C6\u30CD\u30B9\u306E\u7BE9\u306B\u3088\u308B\u7D20\
  \u6570\u5217\u6319"
---
