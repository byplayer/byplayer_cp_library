#ifndef BCPL_DIJKSTRA_HPP
#define BCPL_DIJKSTRA_HPP 1

#include <limits>
#include <queue>
#include <utility>
#include <vector>

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpadded"
#endif // __clang__

namespace bcpl {

template <typename C, typename D> struct dijkstra {
  using CostType = C;
  using DistanceType = D;
  using DistancePair = std::pair<DistanceType, std::size_t>;
  using DistancePairVector = std::vector<DistancePair>;
  using DistanceVector = std::vector<DistanceType>;

  struct Node {
    std::size_t to;
    CostType cost;

    Node(const std::size_t p, const CostType c) : to(p), cost(c) {}
  };

  using Graph = std::vector<std::vector<Node>>;

  struct NodeGreater {
    constexpr bool operator()(const Node &x, const Node &y) const {
      return x.cost > y.cost;
    }
  };

public:
  static DistanceVector calculate(const Graph &graph, const std::size_t start) {
    DistanceVector distances(graph.size(),
                             std::numeric_limits<DistanceType>::max());

    distances[start] = 0;
    std::priority_queue<DistancePair, DistancePairVector,
                        std::greater<DistancePair>>
        q;
    q.emplace(distances[start], start);
    while (!q.empty()) {
      auto [distance, from] = q.top();
      q.pop();
      if (distances[from] < distance) {
        continue;
      }

      for (const auto &edge : graph[from]) {
        const DistanceType d =
            distances[from] + static_cast<DistanceType>(edge.cost);
        if (d < distances[edge.to]) {
          distances[edge.to] = d;
          q.emplace(distances[edge.to], edge.to);
        }
      }
    }
    return distances;
  }
};
} // namespace bcpl

#ifdef __clang__
#pragma clang diagnostic pop
#endif // __clang__
#endif // BCPL_DIJKSTRA_HPP
