#include <bits/stdc++.h>
using namespace std;

struct Edge {
  int to;        // 终点
  int open_time; // 这条边最早可以通过的时刻
};

struct State {
  int vertex;    // 当前所在的点
  int remainder; // 当前时刻除以 k 的余数
};

const long long INF = (1LL << 60);

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m, k;
  cin >> n >> m >> k;

  // g[u] 保存所有从 u 出发的有向边。
  vector<vector<Edge>> g(n + 1);
  for (int i = 0; i < m; ++i) {
    int from, to, open_time;
    cin >> from >> to >> open_time;
    g[from].push_back({to, open_time});
  }

  // dist[u][r]：到达 u 且到达时刻 mod k = r 时，最早的真实到达时刻。
  vector<vector<long long>> dist(n + 1, vector<long long>(k, INF));

  // 普通队列只负责保存“距离变小、需要继续向外松弛”的状态。
  // 同一个状态可能被多次更新，因此这不是“每个点只访问一次”的普通 BFS。
  queue<State> q;
  vector<vector<char>> in_queue(n + 1, vector<char>(k, false));

  // 0 时刻乘车到达入口，所以初始状态是 (1, 0)。
  dist[1][0] = 0;
  q.push({1, 0});
  in_queue[1][0] = true;

  while (!q.empty()) {
    State current = q.front();
    q.pop();

    int u = current.vertex;
    int remainder = current.remainder;
    in_queue[u][remainder] = false;

    for (const Edge &edge : g[u]) {
      long long use_edge_time = dist[u][remainder];

      if (use_edge_time < edge.open_time) {
        // 景区内不能原地等待。这里增加若干个 k，不表示在 u 等待，
        // 而是把乘入口巴士的时刻整体推迟若干个 k。
        // 整条已走路径的时刻会同时后移，余数不变，且之前的边仍然开放。
        long long difference = edge.open_time - use_edge_time;
        long long periods = (difference + k - 1) / k;
        use_edge_time += periods * k;
      }

      // 每条道路恰好走 1 个单位时间。
      long long next_time = use_edge_time + 1;
      int next_remainder = next_time % k;

      // 松弛状态 (edge.to, next_remainder)。
      if (next_time >= dist[edge.to][next_remainder]) {
        continue;
      }

      dist[edge.to][next_remainder] = next_time;

      // 若该状态已经在队列中，不必重复加入；它出队时会读取最新的 dist。
      if (!in_queue[edge.to][next_remainder]) {
        q.push({edge.to, next_remainder});
        in_queue[edge.to][next_remainder] = true;
      }
    }
  }

  // 离开景区的时刻必须是 k 的倍数，所以只接受余数为 0 的终点状态。
  if (dist[n][0] == INF) {
    cout << -1 << '\n';
  } else {
    cout << dist[n][0] << '\n';
  }

  return 0;
}
