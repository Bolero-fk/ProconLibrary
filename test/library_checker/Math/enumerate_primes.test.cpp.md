---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: Math/enumerate_primes.hpp
    title: "\u30A8\u30E9\u30C8\u30B9\u30C6\u30CD\u30B9\u306E\u7BE9\u306B\u3088\u308B\
      \u7D20\u6570\u5217\u6319"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/enumerate_primes
    links:
    - https://judge.yosupo.jp/problem/enumerate_primes
  bundledCode: "#line 1 \"test/library_checker/Math/enumerate_primes.test.cpp\"\n\
    #define PROBLEM \"https://judge.yosupo.jp/problem/enumerate_primes\"\n\n#include\
    \ <Math/enumerate_primes.hpp>\n#include <bits/stdc++.h>\n\nusing namespace std;\n\
    \nint main()\n{\n    long long N, A, B;\n    cin >> N >> A >> B;\n\n    PrimesEnumerator\
    \ primesEnumerator(N);\n\n    long long piN = primesEnumerator.primes.size();\n\
    \n    vector<long long> ps;\n    for (int i = B; i < piN; i += A)\n    {\n   \
    \     ps.push_back(primesEnumerator.primes[i]);\n    }\n\n    long long X = ps.size();\n\
    \n    cout << piN << \" \" << X << endl;\n\n    for (long long p : ps)\n    {\n\
    \        cout << p << \" \";\n    }\n    cout << endl;\n\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/enumerate_primes\"\n\n\
    #include <Math/enumerate_primes.hpp>\n#include <bits/stdc++.h>\n\nusing namespace\
    \ std;\n\nint main()\n{\n    long long N, A, B;\n    cin >> N >> A >> B;\n\n \
    \   PrimesEnumerator primesEnumerator(N);\n\n    long long piN = primesEnumerator.primes.size();\n\
    \n    vector<long long> ps;\n    for (int i = B; i < piN; i += A)\n    {\n   \
    \     ps.push_back(primesEnumerator.primes[i]);\n    }\n\n    long long X = ps.size();\n\
    \n    cout << piN << \" \" << X << endl;\n\n    for (long long p : ps)\n    {\n\
    \        cout << p << \" \";\n    }\n    cout << endl;\n\n    return 0;\n}"
  dependsOn:
  - Math/enumerate_primes.hpp
  isVerificationFile: true
  path: test/library_checker/Math/enumerate_primes.test.cpp
  requiredBy: []
  timestamp: '2023-11-30 00:57:41+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/library_checker/Math/enumerate_primes.test.cpp
layout: document
redirect_from:
- /verify/test/library_checker/Math/enumerate_primes.test.cpp
- /verify/test/library_checker/Math/enumerate_primes.test.cpp.html
title: test/library_checker/Math/enumerate_primes.test.cpp
---
