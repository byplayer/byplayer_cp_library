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

/**
 * @brief Library for finding shortest path using Dijkstra
 * method(ダイクストラ法で最短経路を求めるライブラリ)
 *
 * @tparam D destination position type @n
 *           expect: int, unsigned int, long long, unsigned long long @n
 *           位置情報保存用のタイプ @n
 *           期待値: int, unsigned int, long long, unsigned long long
 *
 * @tparam C cost value type @n
 *         expect: int, unsigned int, long long, unsigned long long @n
 *         コストの値用のタイプ @n
 *         期待値: int, unsigned int, long long, unsigned long long
 * )
 *
 * This library finds shortest path using Dijkstra method.
 *
 * これは、ダイクストラ法で最短経路を求めるライブラリです。
 *
 * There are paths as follow.
 * [num] is destination. (num) is cost to move.
 *
 * 以下のような経路があるとします。
 * [数字] は目的地。[数値] は移動時のコスト。
 *
 * <PRE>
 * [0] -(100)- [2] -(10)- [4]
 *   └ -( 10)- [3] -(10)┘
 * </PRE>
 *
 * There are two paths from 1 to 4. In this case you need prepare
 * Graph object as follow and call calculate method. Then, you
 * receive destination and cost vector. You can get destination
 * cost value when you access destination value of return vector.
 *
 * 1から4まで到達するのに2つの経路があります。この時、以下のようなGraphオブジェクト
 * を準備し、 calculate 関数を呼び出します。関数の戻り値の目的地の値を取得する
 * 事で、目的地までのコストを取得できます。
 *
 * @code{.cpp}
 * #include "bcpl/types"
 * using Dijkstra = bcpl::dijkstra<bcpl::ll, int>;
 *
 * graph[0].emplace_back(1, 100);
 * graph[0].emplace_back(2, 10);
 * graph[1].emplace_back(3, 10);
 * graph[2].emplace_back(3, 10);
 *
 * ASSERT(graph[3] == 20);
 * @endcode
 *
 * If the destination is unreachable, you will get
 * bcpl::dijkstra<D, C>::INF() value as result.
 *
 * もし、目的地に到達できない場合は bcpl::dijkstra<D, C>::INF() の値が
 * 取得できる。
 *
 * @code{.cpp}
 * #include "bcpl/types"
 * using Dijkstra = bcpl::dijkstra<bcpl::ll, int>;
 *
 * Dijkstra::Graph graph(3);
 * graph[0].push_back({1, 100});
 * auto distances = Dijkstra::calculate(graph, 0);
 * ASSERT(distances[2] == Dijkstra::INF());
 * @endcode
 */
template <typename D, typename C> struct dijkstra {
  /**
   * @brief The cost value type @n
   * コスト値用の型
   */
  using CostType = C;

  /**
   * @brief The destination value type @n
   * 目的地用の型
   */
  using DistanceType = D;
  using DistancePair = std::pair<DistanceType, std::size_t>;
  using DistancePairVector = std::vector<DistancePair>;

  /**
   * @brief distance and cost vector @n
   * 目的地とコストのvector
   *
   * This value is used as calculate method return value.
   * vector key is destination position. And value is cost.
   *
   * この値は calculate 関数の戻り地として使われます。
   * vectorのキーは、目的地の場所で、値はコストになります。
   */
  using DistanceVector = std::vector<DistanceType>;
  static constexpr DistanceType INF() {
    return std::numeric_limits<DistanceType>::max();
  }

  /**
   * @brief destination and cost object. This is used for Graph @n
   * 目的値とコストのオブジェクト。 Graphで使われる事を想定。
   */
  struct Node {
    std::size_t to;
    CostType cost;

    Node(const size_t t, const CostType c) : to(t), cost(c) {}
  };

  /**
   * @brief Graph object @n
   * グラフオブジェクト
   *
   * The vector key is current position. The values(vector) are
   * reachable destinations and cost vector.
   *
   * この vector のキーは 現在の場所です。値(vector)ha,
   * 現在の場所から到達できる場所とコストの vector です。
   */
  using Graph = std::vector<std::vector<Node>>;

  struct NodeGreater {
    constexpr bool operator()(const Node &x, const Node &y) const {
      return x.cost > y.cost;
    }
  };

public:
  /**
   * @brief calculate the shortest paths using dijkstra method @n
   *        ダイクストラ法を使って最短経路を求める
   *
   * @param graph paths graph @n 経路を表すグラフ
   * @param start start position @n 開始位置
   * @return DistanceVector cost of each destination @n
   *         それぞれの場所へ到達するためのコスト
   */
  static DistanceVector calculate(const Graph &graph, const std::size_t start) {
    DistanceVector distances(graph.size(), INF());

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
