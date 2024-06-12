#ifndef BCPL_UTILITY_HPP
#define BCPL_UTILITY_HPP 1
/*
 * bcpl: https://byplayer.github.io/byplayer_cp_library/
 */

#include <ostream>
#include <utility>

namespace bcpl {

template <typename T1, typename T2>
std::ostream &operator<<(std::ostream &os, const std::pair<T1, T2> &p) {
  os << "(" << p.first << "," << p.second << ")";
  return os;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &v) {
  for (size_t i = 0; i < v.size(); ++i) {
    if (i) {
      os << " ";
    }
    os << v[i];
  }
  return os;
}

template <typename T>
std::ostream &operator<<(std::ostream &os,
                         const std::vector<std::vector<T>> &vv) {
  for (auto &&v : vv) {
    os << v << std::endl;
  }
  return os;
}

} // namespace bcpl

#endif // BCPL_UTILITY_HPP
