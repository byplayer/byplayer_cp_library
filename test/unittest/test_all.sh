#!/bin/bash

set -eu

# Fix Git ownership issue in Docker (ignore errors if not in git repo)
git config --global --add safe.directory '*' 2>/dev/null || true

function make_test() {
    CXX=$1
    CXX_VER=$2
    echo "Testing ${CXX} with C++${CXX_VER}"

    # Navigate to project root for CMake
    cd /bcpl

    # Configure and build with CMake
    cmake -S . -B build-${CXX}-${CXX_VER} \
          -DCMAKE_CXX_COMPILER=${CXX} \
          -DCMAKE_CXX_STANDARD=${CXX_VER#c++} \
          -DCMAKE_BUILD_TYPE=Release \
          -DFETCHCONTENT_FULLY_DISCONNECTED=OFF \
          -DFETCHCONTENT_UPDATES_DISCONNECTED=OFF

    cmake --build build-${CXX}-${CXX_VER} -j --target run_tests

    echo "Completed testing with ${CXX} C++${CXX_VER}"
    echo "----------------------------------------"
}

# Test with various compiler and standard combinations
make_test clang++ 23
make_test clang++ 20
make_test clang++ 17
make_test g++ 23
make_test g++ 20
make_test g++ 17
