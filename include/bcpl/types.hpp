#ifndef BCPL_TYPES_HPP
#define BCPL_TYPES_HPP 1
/*
 * bcpl: https://byplayer.github.io/byplayer_cp_library/
 */

#include <algorithm>
#include <cmath>
#include <string>
#include <vector>

namespace bcpl {
using ll = long long;
using ull = unsigned long long;
using uint = unsigned int;

#ifdef __clang__
using i128 = __int128;
#elif __GNUC__
using i128 = __uint128_t;
#endif // __clang__

using VI = std::vector<int>;
using VVI = std::vector<VI>;

using VLL = std::vector<bcpl::ll>;
using VVLL = std::vector<VLL>;

using VS = std::vector<std::string>;
} // namespace bcpl
#endif // BCPL_TYPES_HPP
