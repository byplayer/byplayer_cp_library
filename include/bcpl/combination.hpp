#ifndef BCPL_COMBINATION_HPP
#define BCPL_COMBINATION_HPP 1
/*
 * bcpl: https://byplayer.github.io/byplayer_cp_library/
 */

#include <algorithm>
#include <iterator>
#include <numeric>
#include <vector>

namespace bcpl_prv {
/**
 * @brief This is combination helper function. Don't call this directory. @n
 * コンビネーション処理ヘルパ関数。直接呼び出さないこと。
 *
 * @tparam T array type
 * @tparam F callback function type
 * @param arr original array
 * @param idx start index
 * @param r remaining combination count
 * @param pattern combination result array
 * @param callback callback function
 * @return true if call back return true or reach end.
 * @return false if call back function return false.
 */
template <typename T, typename F>
bool dfs_combination(T &arr, size_t idx, size_t r, T &pattern, F &&callback) {
  if (r == 0) {
    if (!callback(pattern)) {
      return false;
    }
    return true;
  }
  if ((idx + r) > arr.size()) {
    return true;
  }

  // select
  pattern.push_back(arr[idx]);
  if (!dfs_combination(arr, idx + 1, r - 1, pattern, callback)) {
    return false;
  }
  pattern.pop_back();
  // not select
  if (!dfs_combination(arr, idx + 1, r, pattern, callback)) {
    return false;
  }
  return true;
}

} // namespace bcpl_prv

namespace bcpl {
/**
 * @brief Call callback function with all containers items combination  @n
 *        引数のコンテナの要素の全組合せを引数ににcallback 関数を呼びます
 *
 * @tparam T container type(expect bi-direction iterator) @n
 *           コンテナ型(双方向イテレータを持っていることを期待しています)
 * @tparam F callback function type.
 *           expect: bool func(const T &v, long long k) @n
 *           コールバック関数型: bool func(const T &v, long long k)
 *           の関数を期待しています
 * @param v  container for listing the combination @n
 *           組合せを列挙するコンテナ
 * @param k  Number of elements in the combination @n
 *           組合せの要素数
 * @param callback The callback function.
 *                 expect: bool func(const T &v) @n
 *                 コールバック関数。以下の型を期待しています。
 *                 bool func(const T &v)
 *
 * Reorder argument v to list all combination. The first k elements
 * are target elements. If there are elements with the same value, they are
 * regarded as the same combination and are not listed. If you list all
 * combination even if container includes equals elements, please call @link
 * foreach_combination_all @endlink function.
 * The callback function is called each combination. If you return @b true in
 * the callback function, continue listing combination. If you return @b false
 * in the callback function, abort listing combination.
 *
 * 全組合せを列挙するために、引数 v の 要素を並び替えていく。先頭 k 個が組合せ
 * の要素となっています。同値の要素がある場合は、同じ組合せとみなし列挙はしません。
 * 重複要素があってもすべての組合せを列挙したい場合は、 @link
 * foreach_combination_all @endlink 関数を呼び出してください。
 * コールバック関数がそれぞれの組合せ毎に呼び出されます。もし、コールバック関数から
 * @b true が返った場合は、列挙を続けます。もし、コールバック関数から @b false
 * が返った場合は、列挙を中断します。
 *
 * example: normal case
 * @code{.cpp}
 * #include "bcpl/combination"
 * #include <cassert>
 * #include <vector>
 *
 * int main() {
 *   using VI = std::vector<int>;
 *   using VVI = std::vector<VI>;
 *   VI v = {0, 1, 2};
 *   VI original = v;
 *   VVI combinations;
 *
 *   bcpl::foreach_combination(v, 2, [&combinations](const VI &v) {
 *     combinations.push_back({v[0], v[1]});
 *     return true;
 *   });
 *
 *   assert(combinations.size() == static_cast<size_t>(3));
 *   assert(combinations[0] == VI({0, 1}));
 *   assert(combinations[1] == VI({0, 2}));
 *   assert(combinations[2] == VI({1, 2}));
 *   assert(v == original);
 *   return 0;
 * }
 * @endcode
 *
 * example: same elements
 * @code{.cpp}
 * #include "bcpl/combination"
 * #include <cassert>
 * #include <vector>
 *
 * int main() {
 *   using VI = std::vector<int>;
 *   using VVI = std::vector<VI>;
 *   VI v = {1, 1, 2};
 *   VI original = v;
 *   VVI combinations;
 *
 *   bcpl::foreach_combination(v, 2, [&combinations](const VI &v) {
 *     combinations.push_back({v[0], v[1]});
 *     return true;
 *   });
 *
 *   assert(combinations.size() == static_cast<size_t>(2));
 *   assert(combinations[0] == VI({1, 1}));
 *   assert(combinations[1] == VI({1, 2}));
 *   assert(v == original);
 *   return 0;
 * }
 * @endcode
 *
 * example: break in the middle
 * @code{.cpp}
 * #include "bcpl/combination"
 * #include <cassert>
 * #include <vector>
 *
 * int main() {
 *   using VI = std::vector<int>;
 *   using VVI = std::vector<VI>;
 *   VI v = {0, 1, 2};
 *   VI original = v;
 *   VVI combinations;
 *
 *   int i = 0;
 *   bcpl::foreach_combination(v, 2,
 *                             [&combinations, &i](const VI &v, long long k) {
 *                               combinations.push_back({v[0], v[1]});
 *                               ++i;
 *                               if (i == 2) {
 *                                 return false;
 *                               }
 *                               return true;
 *                             });
 *
 *   assert(combinations.size() == static_cast<size_t>(2));
 *   assert(combinations[0] == VI({0, 1}));
 *   assert(combinations[1] == VI({0, 2}));
 *   assert(v != original);
 *   return 0;
 * }
 * @endcode
 */
template <typename T, typename F>
void foreach_combination(T &v, size_t k, F &&callback) {
  if (v.empty() || v.size() < static_cast<std::size_t>(k) || k == 0) {
    return;
  }

  T arr;
  bcpl_prv::dfs_combination(v, 0, k, arr, callback);
}
} // namespace bcpl

#endif // BCPL_COMBINATION_HPP
