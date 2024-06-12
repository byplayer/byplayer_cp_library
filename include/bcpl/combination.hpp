#ifndef BCPL_COMBINATION_HPP
#define BCPL_COMBINATION_HPP 1
/*
 * bcpl: https://byplayer.github.io/byplayer_cp_library/
 */

#include <algorithm>
#include <iterator>
#include <numeric>
#include <vector>

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
 *                 expect: bool func(const T &v, long long k) @n
 *                 コールバック関数。以下の型を期待しています。
 *                 bool func(const T &v, long long k)
 *
 * Reorder argument v to list all combination. The first k elements
 * are target elements. If there are elements with the same value, they are
 * regarded as the same combination and are not listed. If you list all
 * combination even if container includes equals elements, please call @link
 * foreach_combination_all @endlink function.
 * The callback function is called each combination. If you return @b true in
 * the callback function, continue listing combination. If you return @b false
 * in the callback function, abort listing combination. In this case, argument
 * container may be different order than it was before this function was called.
 *
 * 全組合せを列挙するために、引数 v の 要素を並び替えていく。先頭 k 個が組合せ
 * の要素となっています。同値の要素がある場合は、同じ組合せとみなし列挙はしません。
 * 重複要素があってもすべての組合せを列挙したい場合は、 @link
 * foreach_combination_all @endlink 関数を呼び出してください。
 * コールバック関数がそれぞれの組合せ毎に呼び出されます。もし、コールバック関数から
 * @b true が返った場合は、列挙を続けます。もし、コールバック関数から @b false
 * が返った
 * 場合は、列挙を中断します。この場合、引数のコンテナの並び順は関数の呼び出し前と
 * 異なる順番になっている場合があります。
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
 *   bcpl::foreach_combination(v, 2, [&combinations](const VI &v, long long k) {
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
 *   bcpl::foreach_combination(v, 2, [&combinations](const VI &v, long long k) {
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
void foreach_combination(T &v, long long k, F &&callback) {
  if (v.empty() || v.size() < static_cast<std::size_t>(k) || k == 0) {
    return;
  }
  if (!callback(v, k)) {
    return;
  }

  const auto first = v.begin();
  const auto last = v.end();
  auto subset = std::next(first, k);
  if (subset == last) {
    return;
  }
  auto src = subset;

  while (first != src) {
    src--;
    if (*src < *(last - 1)) {
      auto dest = subset;
      while (*src >= *dest) {
        dest++;
      }
      std::iter_swap(src, dest);
      std::rotate(src + 1, dest + 1, last);
      std::rotate(subset, subset + (last - dest) - 1, last);
      if (!callback(v, k)) {
        return;
      }
    }
  }

  std::rotate(first, subset, last);
}

/**
 * @brief Call callback function with all containers items combination even if
 * it includes same elements  @n
 *        引数のコンテナの要素が同一の値を含んていてもの全組合せを引数ににcallback
 *        関数を呼びます
 *
 * @tparam T container type(expect bi-direction iterator) @n
 *           コンテナ型(双方向イテレータを持っていることを期待しています)
 * @tparam F callback function type.
 *           expect: bool func(const T &v) @n
 *           コールバック関数型: bool func(const T &v)
 *           の関数を期待しています
 * @param v  container for listing the combination @n
 *           組合せを列挙するコンテナ
 * @param k  Number of elements in the combination @n
 *           組合せの要素数
 * @param callback The callback function.
 *                 expect: bool func(const T &v) @n
 *                 コールバック関数。以下の型を期待しています
 *                 bool func(const T &v)
 *
 * Call the callback function with element set vector which includes only
 * combination data. The basic usage is almost same as @link foreach_combination
 * @endlink function but this function list all combination set even if
 * container includes equal element with some same data set. The callback
 * function is called each combination. If you return @b true in the callback
 * function, continue listing combination. If you return @b false in the
 * callback function, abort listing combination. Even if you abort listing,
 * original vector order isn't changed.
 *
 * 組合せの要素を含む配列を引数にコールバック関数を呼び出す。基本的な使い方は
 * @link foreach_combination
 * @endlink
 * 関数と同じですが、この関数はコンテナの要素に同じ値を含んていても重複した組合せも含め
 * 全ての組合せを列挙します。
 * コールバック関数がそれぞれの組合せ毎に呼び出されます。もし、コールバック関数から
 * @b true が返った場合は、列挙を続けます。もし、コールバック関数から @b false
 * が返った
 * 場合は、列挙を中断します。この場合でも、引数のコンテナの並び順に変更はありません。
 */
template <typename T, typename F>
void foreach_combination_all(const T &v, long long k, F &&callback) {
  using VS = std::vector<size_t>;
  VS wv(v.size());
  std::iota(wv.begin(), wv.end(), 0);

  T combi(static_cast<std::size_t>(k));
  foreach_combination(wv, k,
                      [&v, &combi, &callback](const VS &cv, long long ck) {
                        for (long long i = 0; i < ck; ++i) {
                          combi[static_cast<std::size_t>(i)] =
                              v[cv[static_cast<std::size_t>(i)]];
                        }
                        return callback(combi);
                      });
}
} // namespace bcpl

#endif // BCPL_COMBINATION_HPP
