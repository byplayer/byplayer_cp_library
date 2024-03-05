#include "bcpl/math"
#include "gtest_include.hpp"

TEST(math, pow_mod) {
  ASSERT_EQ(bcpl::pow_mod<bcpl::i128>(10, 2, 1000), 100);
  ASSERT_EQ(bcpl::pow_mod<bcpl::i128>(10, 5, 1000), 0);
  ASSERT_EQ(bcpl::pow_mod<bcpl::ll>(10, 2, 1000), 100);
  ASSERT_EQ(bcpl::pow_mod<bcpl::ll>(10, 5, 1000), 0);
  ASSERT_EQ(bcpl::pow_mod<int>(10, 2, 1000), 100);
  ASSERT_EQ(bcpl::pow_mod<int>(10, 5, 1000), 0);
}

TEST(math, is_prime) {
  ASSERT_EQ(bcpl::is_prime(-100), false);
  ASSERT_EQ(bcpl::is_prime(0), false);
  ASSERT_EQ(bcpl::is_prime(1), false);
  ASSERT_EQ(bcpl::is_prime(2), true);
  ASSERT_EQ(bcpl::is_prime(4), false);
  ASSERT_EQ(bcpl::is_prime(6), false);
  ASSERT_EQ(bcpl::is_prime(13649), true);
}

TEST(math, pollard) {
  ASSERT_EQ(bcpl::pollard(0), 2);
  ASSERT_EQ(bcpl::pollard(1), -1);
  ASSERT_EQ(bcpl::pollard(2), 2);
  ASSERT_EQ(bcpl::pollard(4), 2);
  ASSERT_EQ(bcpl::pollard(6), 2);
  ASSERT_EQ(bcpl::pollard(27), 3);
  ASSERT_EQ(bcpl::pollard(13 * 17), 13);
  ASSERT_EQ(bcpl::pollard(18), 2);
  ASSERT_EQ(bcpl::pollard(49), 7);
  ASSERT_EQ(bcpl::pollard(13649), 13649);
}

TEST(math, prime_factorize) {
  ASSERT_EQ(bcpl::prime_factorize(2), bcpl::VLL({2}));
  ASSERT_EQ(bcpl::prime_factorize(4), bcpl::VLL({2, 2}));
  ASSERT_EQ(bcpl::prime_factorize(14), bcpl::VLL({2, 7}));
  ASSERT_EQ(bcpl::prime_factorize(49), bcpl::VLL({7, 7}));
  ASSERT_EQ(bcpl::prime_factorize(3 * 3 * 5 * 13), bcpl::VLL({3, 3, 5, 13}));
  ASSERT_EQ(bcpl::prime_factorize(13649), bcpl::VLL({13649}));
}
