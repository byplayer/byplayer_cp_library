#!/bin/bash

set -eu

function make_test() {
    CXX=$1
    CXX_VER=$2
    echo test ${CXX} with ${CXX_VER}
    make CXX=${CXX} CXX_VER=${CXX_VER} test
}

make_test clang++ c++2b
make_test clang++ c++20
make_test clang++ c++17
make_test g++ c++23
make_test g++ c++20
make_test g++ c++17
