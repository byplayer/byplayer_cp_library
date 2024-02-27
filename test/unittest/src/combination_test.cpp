#include "bcpl/combination"
#include "bcpl/types"
#include "gtest_include.hpp"
#include <vector>

using namespace std;

namespace {
using VI = std::vector<int>;
using VVI = std::vector<VI>;
} // namespace

TEST(combination, basic) {
  VI v = {0, 1, 2};
  const VI original = v;
  VVI res;

  bcpl::foreach_combination(v, 2, [&res](const VI &vf, bcpl::ll /* k */) {
    res.push_back({vf[0], vf[1]});
    return true;
  });

  ASSERT_EQ(res.size(), static_cast<size_t>(3));
  ASSERT_EQ(res[0], VI({0, 1}));
  ASSERT_EQ(res[1], VI({0, 2}));
  ASSERT_EQ(res[2], VI({1, 2}));
  ASSERT_EQ(v, original);
}

TEST(combination, including_same_value) {
  VI v = {1, 1, 2};
  VVI res;

  bcpl::foreach_combination(v, 2, [&res](const VI &vf, bcpl::ll /* k */) {
    res.push_back({vf[0], vf[1]});
    return true;
  });

  ASSERT_EQ(res.size(), static_cast<size_t>(2));
  ASSERT_EQ(res[0], VI({1, 1}));
  ASSERT_EQ(res[1], VI({1, 2}));
}

TEST(combination, empty_vector) {
  VI v;
  VVI res;

  bcpl::foreach_combination(v, 2, [&res](const VI &vf, bcpl::ll /* k */) {
    res.push_back({vf[0], vf[1]});
    return true;
  });

  ASSERT_EQ(res.size(), static_cast<size_t>(0));
}

TEST(combination, break_first) {
  VI v = {0, 1, 2};
  const VI original = v;
  VVI res;

  bcpl::foreach_combination(v, 2, [&res](const VI &vf, bcpl::ll /* k */) {
    res.push_back({vf[0], vf[1]});
    return false;
  });

  ASSERT_EQ(res.size(), static_cast<size_t>(1));
  ASSERT_EQ(res[0], VI({0, 1}));
  ASSERT_EQ(v, original);
}

TEST(combination, break_middle) {
  VI v = {0, 1, 2};
  const VI original = v;
  VVI res;

  int i = 0;
  bcpl::foreach_combination(v, 2, [&res, &i](const VI &vf, bcpl::ll /* k */) {
    res.push_back({vf[0], vf[1]});
    ++i;
    if (i == 2) {
      return false;
    }
    return true;
  });

  ASSERT_EQ(res.size(), static_cast<size_t>(2));
  ASSERT_EQ(res[0], VI({0, 1}));
  ASSERT_EQ(res[1], VI({0, 2}));
  ASSERT_NE(v, original);
}

TEST(combination, same_count) {
  VI v = {0, 1, 2};
  const VI original = v;
  VVI res;

  bcpl::foreach_combination(v, 3, [&res](const VI &vf, bcpl::ll /* k */) {
    res.push_back({vf[0], vf[1], vf[2]});
    return true;
  });

  ASSERT_EQ(res.size(), static_cast<size_t>(1));
  ASSERT_EQ(res[0], VI({0, 1, 2}));
  ASSERT_EQ(v, original);
}

TEST(combination, over_count) {
  VI v = {0, 1, 2};
  const VI original = v;
  VVI res;

  bcpl::foreach_combination(v, 4, [&res](const VI &vf, bcpl::ll /* k */) {
    res.push_back({vf[0], vf[1]});
    return true;
  });

  ASSERT_EQ(res.size(), static_cast<size_t>(0));
  ASSERT_EQ(v, original);
}
