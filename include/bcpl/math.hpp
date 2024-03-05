#ifndef BCPL_NUMERIC_HPP
#define BCPL_NUMERIC_HPP 1

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-prototypes"
#endif // __clang__

#include "bcpl/types"
#include <algorithm>
#include <numeric>
#include <vector>

namespace bcpl {
/**
 * @brief calculate a ** n mod m @n
 *                  a の n 乗 mod m を求めます
 *
 * @tparam T target calculate integer type(int, long long, etc) @n
 *           計算対象の整数型 (int, long long など)
 * @param a Number to be raised to power @n
 *          累乗される数
 * @param n raising a number to a power @n
 *          累乗する数
 * @param m modulo operation base number @n
 *          あまりを求める割る数
 * @return T The result of (a ** n) % m @n
 *         (a ** n) % m の計算結果
 */
template <class T> T pow_mod(T a, T n, T m) {
  if (m == 1) {
    return 0;
  }

  T res = 1 % m;
  a %= m;
  while (n) {
    if (n & 1)
      res = (res * a) % m;
    a = (a * a) % m;
    n >>= 1;
  }
  return res;
}

/**
 * @brief Determines whether a number is prime or not @n
 *        素数かどうかの判定を行います
 *
 * @param n Target number @n
 *          判定対象の数字
 * @return true If n is prime number @n
 *              nが素数の場合
 * @return false If n is NOT prime number @n
 *               nが素数でない場合
 */
bool is_prime(bcpl::ll n) {
  if (n <= 1) {
    return false;
  }

  if (n == 2 || n == 3) {
    return true;
  }

  if ((n % 2) == 0) {
    return false;
  }

  const VLL A = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
  bcpl::ll s = 0;
  bcpl::ll d = n - 1;
  while ((d % 2) == 0) {
    ++s;
    d >>= 1;
  }

  for (auto a : A) {
    if ((a % n) == 0) {
      return true;
    }

    bcpl::ll x = static_cast<bcpl::ll>(bcpl::pow_mod<i128>(a, d, n));
    if (x != 1) {
      bcpl::ll t;
      for (t = 0; t < s; ++t) {
        if (x == n - 1)
          break;
        x = (static_cast<bcpl::i128>(x) * x) % n;
      }
      if (t == s)
        return false;
    }
  }
  return true;
}

/**
 * @brief The function returns the smallest prime divisible of n @n
 *        nを割り切れるの最小の素数を返関数
 *
 * If n is 0, return 2. And if n is 1, return -1. @n
 * もし n が 0 の場合は 2 を返します。また、
 *
 * @param n The number to calculate the smallest prime divisible number
 * @return bcpl::ll The smallest prime divisible number of n @n
 *                  nを割り切れるの最小の素数
 */
bcpl::ll pollard(const bcpl::ll n) {
  if ((n % 2) == 0) {
    return 2;
  }

  if (n == 1) {
    return -1;
  }

  if (is_prime(n)) {
    return n;
  }

  bcpl::ll step = 0;
  auto f = [&](bcpl::ll x) -> bcpl::ll {
    return (static_cast<i128>(x) * x + step) % n;
  };

  bcpl::ll x, y, p;
  while (true) {
    ++step;
    x = 1;
    y = f(x);
    while (true) {
      p = std::gcd(y - x + n, n);
      if (p == 0 || p == n) {
        break;
      }

      if (p != 1) {
        return p;
      }

      x = f(x);
      y = f(f(y));
    }
  }

  return -1;
}

/**
 * @brief Prime factorize @n
 *        素因数分解をする関数
 *
 * Returns a vector of prime factorized elements sorted in descending order as
 * follows.
 * If there are duplicate elements, they are not omitted and all duplicate
 * elements are returned.
 *
 * 以下のように素因数分解した要素を降順でソートした vector を返します。
 * 重複要素がある場合は省略せず重複要素も全て返します。
 *
 * @code
 *   42 -> {2, 3, 7}
 *   8 -> {2, 2, 2}
 * @endcode
 *
 * @param n Number to be prime factorized @n
 *          素因数分解する数字
 * @return bcpl::VLL prime factorized numbers vector @n
 *                   素因数分解
 */
bcpl::VLL prime_factorize(const bcpl::ll n) {
  if (n <= 1) {
    return {};
  }

  bcpl::ll p = bcpl::pollard(n);
  if (p == n) {
    return {p};
  }

  bcpl::VLL left = prime_factorize(p);
  bcpl::VLL right = prime_factorize(n / p);
  left.insert(left.end(), right.begin(), right.end());
  std::sort(left.begin(), left.end());
  return left;
}
} // namespace bcpl

#ifdef __clang__
#pragma clang diagnostic pop
#endif // __clang__

#endif // BCPL_NUMERIC_HPP
