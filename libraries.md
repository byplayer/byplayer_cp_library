# libraries

## Finding shortest path(最短経路探索)

### [Dijkstra method(ダイクストラ法)](dc/d3b/structbcpl_1_1dijkstra.html)

```cpp
#include "bcpl/dijkstra"
```

Solve the scoring path for a path with a single starting point and non-negative weights on the edges.

単一始点で辺に非負の重みがある経路の採点経路を解く。

## permutation and combination(順列組合せ)

There are permutation and combination libraries.

順列と組合せのライブラリ。

### combination(組合せ)

```cpp
#include "bcpl/combination"
```

#### [foreach_combination](d5/da2/namespacebcpl.html#a676f38aa58b7120f705c153a99564601)

List the combination.

組合せを列挙する。

#### [foreach_combination](d5/da2/namespacebcpl.html#a3955c6a9122d5b6461cf2bcc7457a5c0)

List all the combinations even if the container includes equal elements.

コンテナが同値の要素を含んでいても重複した組合せも含め全ての組合せを列挙する。

## math libraries(数学系ライブラリ)

```cpp
#include "bcpl/math"
```

### [pow_mod](d5/da2/namespacebcpl.html#a58c3ca1e46633af7c7fb85a65b28fe62)

calculate a \*\* n mod m.

a の n 乗 mod m を求めます。

### [is_prime](d5/da2/namespacebcpl.html#af6d1ac2a68a6e6958d999935344e2b06)

Determines whether a number is prime or not.

素数かどうかの判定を行います。

### [prime_factorize](d5/da2/namespacebcpl.html#a7acec159c4c16e9cd79216fedca94c48)

Prime factorize.
The `vector<long long>` which includes prime factorized numbers will be returned from this function.

素因数分解をする関数。
素因数分解をした要素を `vector<long long>` で返します。

### [pollard](d5/da2/namespacebcpl.html#ab3f983aaf4888662f1d4b795d9862f5a)

The function returns the smallest prime divisible of n.

n を割り切れるの最小の素数を返関数。

# debug

## [Debug output macro](da/d7b/debug_8hpp.html#a3597115824b294c3f7075beff73b29ac)

The macro for debug out.
