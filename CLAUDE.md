# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## instruction

Never `git commit` even if I request explisitly.

## Purpose

This is a C++ library for competitive programming (競技プログラミング) that provides data structures and algorithms optimized for online judge systems like AtCoder. The library is header-only and designed to be expanded into single source files for submission.

## Build Commands

### Standard Build

```bash
# Default build (C++23 with Clang)
cmake -S . -B build
cmake --build build -j --target run_tests
```

### Compiler and Standard Combinations

```bash
# Specific compiler and standard
cmake -S . -B build-${COMPILER}${STANDARD} -DCMAKE_CXX_COMPILER=${COMPILER} -DCMAKE_CXX_STANDARD=${STANDARD}
cmake --build build-${COMPILER}${STANDARD} -j --target run_tests

# Examples:
# clang++ with C++23: -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_CXX_STANDARD=23
# g++ with C++20: -DCMAKE_CXX_COMPILER=g++ -DCMAKE_CXX_STANDARD=20
```

### Run All Tests

```bash
# Test all compiler/standard combinations
cd test/unittest
./test_all.sh

# Clean build directories
./test_all.sh --clean
```

### Single Test Execution

```bash
# Build and run specific test
cmake --build build --target unittest
./build/test/unittest/unittest --gtest_filter="TestSuite.TestName"
```

### Documentation

```bash
cmake -S . -B build -DBUILD_DOC=ON
cmake --build build --target doc
```

## Library Architecture

### Directory Structure

- `/include/bcpl/`: Custom library headers (dijkstra, fenwicktree, combination, math, modint, etc.)
- `/ac-library/`: AtCoder official library (included as git submodule)
- `/test/unittest/`: GoogleTest-based unit tests
- `/bin/`: Utility scripts including `expander` for combining headers

### Header Organization

The library uses a dual-source approach:

1. **bcpl headers**: Custom implementations in `include/bcpl/` namespace
2. **AtCoder library**: Official AC library in `ac-library/atcoder/` namespace

Headers are designed to be self-contained and can be included as:

```cpp
#include <bcpl/dijkstra>    // Custom library
#include <atcoder/dsu>       // AtCoder library
```

### Library Expansion for Submission

Before submitting to online judges, use the expander tool to combine all included headers into a single file:

```bash
expander main.cpp  # Generates combined.cpp with all dependencies
```

The expander automatically resolves dependencies from both bcpl and atcoder libraries.

## Testing Infrastructure

### CMake Configuration

- Uses FetchContent to automatically download GoogleTest
- Supports matrix testing across multiple compilers (clang++, g++) and standards (C++17/20/23)
- Compiler-specific optimizations and warning flags configured in `test/unittest/CMakeLists.txt`

### macOS with Homebrew LLVM

The build system automatically detects and configures Homebrew LLVM installations with proper libc++ linking.

## CI/CD

GitHub Actions workflow (`ci-cpp.yml`) runs tests in Docker container `byplayer/cxx-build:v202509.01` with all compiler/standard combinations.

## Important Implementation Notes

### Constexpr Limits

The build system sets expanded constexpr limits for template-heavy competitive programming code:

- `-fconstexpr-depth=2147483647`
- `-fconstexpr-steps=214748364` (Clang)
- `-fconstexpr-loop-limit=2147483647` (GCC)

### Build Optimization

Release builds use `-O2` optimization with native CPU tuning (`-mtune=native -march=native`).

### Git Safe Directory

Docker builds require `git config --global --add safe.directory '*'` for proper Git operations.
