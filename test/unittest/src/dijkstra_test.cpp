#include "bcpl/dijkstra"
#include "gtest_include.hpp"

namespace {
using ll = long long;
using Dijkstra = bcpl::dijkstra<ll, int>;
} // namespace

TEST(Dijkstra, cost) {
  Dijkstra::Graph graph(4);
  graph[0].emplace_back(1, 100);
  graph[0].emplace_back(1, 100);
  graph[0].emplace_back(2, 10);
  graph[1].emplace_back(3, 10);
  graph[2].emplace_back(3, 10);

  auto distances = Dijkstra::calculate(graph, 0);
  ASSERT_EQ(20, distances[3]);
}

TEST(Dijkstra, unreachable) {
  Dijkstra::Graph graph(3);
  graph[0].push_back({1, 100});
  auto distances = Dijkstra::calculate(graph, 0);
  ASSERT_EQ(Dijkstra::INF(), distances[2]);
}
