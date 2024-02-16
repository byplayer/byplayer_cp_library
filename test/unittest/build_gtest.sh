#!/bin/bash

set -eu

echo build gtest_clang++
if [ ! -d gtest_clang++ ]; then
    pushd googletest
    mkdir build_clang++
    cd build_clang++
    cmake -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_INSTALL_PREFIX=../../gtest_clang++ ..
    make
    make install
    cd ..
    rm -r build_clang++
    popd
else
    echo gtest_clang++ is already built.
fi

echo build gtest_g++
if [ ! -d gtest_g++ ]; then
    pushd googletest
    mkdir build_g++
    cd build_g++
    cmake -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ -DCMAKE_INSTALL_PREFIX=../../gtest_g++ ..
    make
    make install
    cd ..
    rm -r build_g++
    popd
else
    echo gtest_g++ is already built.
fi
