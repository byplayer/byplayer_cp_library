#ifndef BCPL_MODINT_HPP
#define BCPL_MODINT_HPP 1

/**
 * @brief atcoder::mint のラッパーヘッダ
 *
 * clang で多数の警告が表示されるのを抑制するのが目的です。
 */

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wold-style-cast"
#pragma clang diagnostic ignored "-Wpadded"
#pragma clang diagnostic ignored "-Wglobal-constructors"
#pragma clang diagnostic ignored "-Wsign-conversion"
#pragma clang diagnostic ignored "-Wmissing-prototypes"
#endif // __clang__

#include <atcoder/modint>

#ifdef __clang__
#pragma clang diagnostic pop
#endif // __clang__

#endif // BCPL_MODINT_HPP
