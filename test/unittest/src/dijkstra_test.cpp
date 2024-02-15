#include "bcpl/dijkstra"

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpadded"
#pragma clang diagnostic ignored "-Wweak-vtables"
#endif // __clang__
#include <gtest/gtest.h>
#ifdef __clang__
#pragma clang diagnostic pop
#endif // __clang__

#ifdef __clang__
#pragma clang diagnostic ignored "-Wglobal-constructors"
#endif // __clang__

namespace {
using ll = long long;
using Dijkstra = bcpl::dijkstra<int, ll>;
} // namespace

TEST(Dijkstra, cost) {
  Dijkstra::Graph graph(3);
  graph[0].emplace_back(Dijkstra::Node(1, 100));
  graph[0].emplace_back(Dijkstra::Node(2, 10));

  auto distances = Dijkstra::calculate(graph, 0);
  ASSERT_EQ(10, distances[2]);
}

TEST(Dijkstra, unreachable) {
  Dijkstra::Graph graph(3);
  graph[0].emplace_back(Dijkstra::Node(1, 100));
  auto distances = Dijkstra::calculate(graph, 0);
  ASSERT_EQ(Dijkstra::INF, distances[2]);
}
