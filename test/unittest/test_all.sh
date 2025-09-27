#!/bin/bash

set -eu

# Fix Git ownership issue in Docker (ignore errors if not in git repo)
git config --global --add safe.directory '*' 2>/dev/null || true

# Check for cleanup option
if [ "${1:-}" = "--clean" ]; then
    echo "Cleaning up build directories..."
    cd /bcpl
    rm -rf build-*
    echo "Build directories removed."
    exit 0
fi

# Track failures
FAILED_TESTS=""
TOTAL_TESTS=0
FAILED_COUNT=0

function make_test() {
    CXX=$1
    CXX_VER=$2
    TOTAL_TESTS=$((TOTAL_TESTS + 1))
    echo "Testing ${CXX} with C++${CXX_VER}"

    # Navigate to project root for CMake
    cd /bcpl

    # Determine number of parallel jobs
    PARALLEL_JOBS=$(nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 4)

    # Configure and build with CMake
    if ! cmake -S . -B build-${CXX}-${CXX_VER} \
          -DCMAKE_CXX_COMPILER=${CXX} \
          -DCMAKE_CXX_STANDARD=${CXX_VER} \
          -DCMAKE_BUILD_TYPE=Release ; then
        echo "ERROR: CMake configuration failed for ${CXX} with C++${CXX_VER}"
        FAILED_TESTS="${FAILED_TESTS}\n  - ${CXX} with C++${CXX_VER}: CMake configuration failed"
        FAILED_COUNT=$((FAILED_COUNT + 1))
        return 1
    fi

    if ! cmake --build build-${CXX}-${CXX_VER} -j${PARALLEL_JOBS} --target run_tests; then
        echo "ERROR: Build or tests failed for ${CXX} with C++${CXX_VER}"
        FAILED_TESTS="${FAILED_TESTS}\n  - ${CXX} with C++${CXX_VER}: Build or tests failed"
        FAILED_COUNT=$((FAILED_COUNT + 1))
        return 1
    fi

    echo "✓ Completed testing with ${CXX} C++${CXX_VER}"
    echo "----------------------------------------"
}

# Test with various compiler and standard combinations
# Continue even if individual tests fail
make_test clang++ 23 || true
make_test clang++ 20 || true
make_test clang++ 17 || true
make_test g++ 23 || true
make_test g++ 20 || true
make_test g++ 17 || true

# Summary report
echo ""
echo "========================================"
echo "Test Summary: ${TOTAL_TESTS} configurations tested"
echo "========================================"

if [ ${FAILED_COUNT} -eq 0 ]; then
    echo "✓ All tests passed successfully!"
    exit 0
else
    echo "✗ ${FAILED_COUNT} test configuration(s) failed:"
    echo -e "${FAILED_TESTS}"
    exit 1
fi
