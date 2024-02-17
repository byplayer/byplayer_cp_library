#!/bin/bash

set -eu

function build_gtest() {
    CC=$1
    CXX=$2
    DEST_DIR=gtest_${CXX}
    BUILD_DIR=build_${CXX}

    echo "build ${DEST_DIR}"
    if [ ! -d ${DEST_DIR} ]; then
        pushd googletest
        if [ -d ${BUILD_DIR} ]; then
            rm -r ${BUILD_DIR}
        fi
        mkdir ${BUILD_DIR}
        cd ${BUILD_DIR}
        cmake -DCMAKE_C_COMPILER=${CC} -DCMAKE_CXX_COMPILER=${CXX} -DCMAKE_INSTALL_PREFIX=../../${DEST_DIR} ..
        make
        make install
        cd ..
        rm -r ${BUILD_DIR}
        popd
    else
        echo ${DEST_DIR} is already built.
    fi
}

set +u
CXX_ARG="$1"
set -u

if [ -z "${CXX_ARG}" ] || [ "${CXX_ARG}" = "clang++" ]; then
    build_gtest 'clang' 'clang++'
fi

if [ -z "${CXX_ARG}" ] || [ "${CXX_ARG}" = "g++" ]; then
    build_gtest 'gcc' 'g++'
fi
