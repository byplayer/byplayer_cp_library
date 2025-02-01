#ifndef BCPL_DEBUG_HPP
#define BCPL_DEBUG_HPP 1
/*
 * bcpl: https://byplayer.github.io/byplayer_cp_library/
 */

#include <iostream>

#ifdef _DEBUG
/**
 * @brief Macro for debug @n
 *        デバッグ用マクロ
 *
 * If _DEBUG is defined, you can cout the value with parameters name.
 * You can call this macro as the blow.
 *
 * @code{.cpp}
 * int n = 3;
 * std::string s("str");
 * DOUT(n, s);
 * @endcode
 *
 * Then you can see the below output in your console.
 *
 * n, s:3, str
 */
#define DOUT(...)                                                              \
  do {                                                                         \
    cout << #__VA_ARGS__ << ":";                                               \
    debug_out(__VA_ARGS__);                                                    \
  } while (0)

namespace bcpl {
void debug_out();

template <class T> void debug_print(T &x, const size_t next_size) {
  std::cout << x;
  if (next_size) {
    std::cout << ", ";
  }
}

void debug_out() { std::cout << std::endl; }

template <class H, class... Ts> void debug_out(H &&h, Ts &&...ts) {
  debug_print(h, sizeof...(ts));
  debug_out(std::forward<Ts>(ts)...);
}
} // namespace bcpl
#else
/**
 * @brief Macro for debug @n
 *        デバッグ用マクロ
 *
 * If _DEBUG is defined, you can cout the value with parameters name.
 * You can call this macro as the blow.
 *
 * @code{.cpp}
 * int n = 3;
 * std::string s("str");
 * DOUT(n, s);
 * @endcode
 *
 * Then you can see the below output in your console.
 *
 * n, s:3, str
 */
#define DOUT(...)                                                              \
  {                                                                            \
    ;                                                                          \
  }
#endif // _DEBUG

#endif // BCPL_DEBUG_HPP
