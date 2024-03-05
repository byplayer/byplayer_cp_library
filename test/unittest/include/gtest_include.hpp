#ifndef BCPL_GTEST_INCLUDE_HPP
#define BCPL_GTEST_INCLUDE_HPP 1

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpadded"
#pragma clang diagnostic ignored "-Wweak-vtables"
#pragma clang diagnostic ignored "-Wunsafe-buffer-usage"
#pragma clang diagnostic ignored "-Wreserved-identifier"
#elif __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-compare"
#endif // __clang__ or __GNUC__

#include <gtest/gtest.h>
#ifdef __clang__
#pragma clang diagnostic pop
#elif __GNUC__
#pragma GCC diagnostic pop
#endif // __clang__

#ifdef __clang__
#pragma clang diagnostic ignored "-Wglobal-constructors"
#elif __GNUC__

#endif // __clang__

#endif // BCPL_GTEST_INCLUDE_HPP
