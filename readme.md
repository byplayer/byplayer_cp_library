[![cpp tests](https://github.com/byplayer/byplayer_cp_library/actions/workflows/ci-cpp.yml/badge.svg?branch=main)](https://github.com/byplayer/byplayer_cp_library/actions/workflows/ci-cpp.yml)
[![CodeQL](https://github.com/byplayer/byplayer_cp_library/actions/workflows/github-code-scanning/codeql/badge.svg?branch=main)](https://github.com/byplayer/byplayer_cp_library/actions/workflows/github-code-scanning/codeql)

# What is this library?

This library aims for competitive programming.

The source code is on [github's byplayer_cp_library](https://github.com/byplayer/byplayer_cp_library).

このライブラリは競技プログラミングを目的に作られています。
ソースコードは、[github の byplayer_cp_library](https://github.com/byplayer/byplayer_cp_library)にあります。

# libraries

There are [library details in the link](df/dc4/md_libraries.html).

[ライブラリの詳細はこのリンクの先](df/dc4/md_libraries.html)にあります。

# How to use this library?

Please clone the source code on any directory.

Next, you add `include` directory to compiler include the path and include
libraries in your source code as follows.

```cpp
#include <bcpl/dijkstra>
```

ソースコードを任意のディレクトリにクローンしてください。
次に、 `include` ディレクトリをコンパイラの include パスへ追加し、以下の用にライブラリを
インクルードして使ってください。

```cpp
#include <bcpl/dijkstra>
```

# expand libraries into your code before submitting

This library is installed only local directory so your source file can not be compiled
on any online judgement system such as [atcoder](https://atcoder.jp/). Therefore, you need to expand libraries beforehand.

このライブラリはローカルディレクトリにインストールされているため、 [atcoder](https://atcoder.jp/)
などのシステムではソースコードがコンパイルできません。
そのため、事前にライブラリを展開(expand)しておく必要があります。

Please add `bin` directory to your `PATH`.
And call `expander` command to your `main.cpp` to expand libraries source
and generate `combined.cpp` before submitting.

`bin` ディレクトリを `PATH` に追加してください。
その後、 `expander` コマンドを `main.cpp` に対して実行し compined.cpp を生成します。

If you call `expander` as below.

以下の用に `expander` コマンドを実行します。

```{.bash}
expander main.cpp
```

As a result, the `combined.cpp` file will be generated. This file includes libraries'
source code before your source code. Therefore, this source code can be compiled
on the online judgment system.

`combined.cpp` ファイルが作られます。このファイルは、ライブラリのソースも含んでいるため
オンラインジャッジメントシステムでコンパイルできます。

# reference

This library is tested with `clang` 17.0.6 `C++23`/`C++20`/`C++17` and
`gcc` 12.2.1 `C++23`/`C++20`/`C++17`.

このライブラリは、`clang` 17.0.6 `C++23`/`C++20`/`C++17` と
`gcc` 12.2.1 `C++23`/`C++20`/`C++17` でテストしています。

# Acknowledgments

The e`xpander.py` is based on and modified from
[ac-library](https://github.com/atcoder/ac-library)'s `expander.py`.
This library version supports both expanding ac-library and this library. So you can combine both ad-library headers and
this library headers.

`expander.py` のソースは
[ac-library](https://github.com/atcoder/ac-library) の `expander.py`
のソースコードをベースにしています。

このライブラリの `expander` は、このライブラリのソースと `ac-library` の両方の
ソースを展開します。

The doxygen document uses [doxygen-awesome-css](https://jothepro.github.io/doxygen-awesome-css/).

doxygen のドキュメントは、 [doxygen-awesome-css](https://jothepro.github.io/doxygen-awesome-css/) を利用しています。

# change log(変更履歴)

The changelog is [here](d3/de2/md_changelog.html).

変更履歴は[こちら](d3/de2/md_changelog.html)にあります。

# License

This library is released under the 3-Clause BSD License.

このライブラリは 3 条項 BSD ライセンスのもとで配布しています。
