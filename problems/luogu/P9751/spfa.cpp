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

const int maxn = 10005;
const long long INF = (1LL << 60);

long long dist[maxn][105];
bool in_queue[maxn][105];
int n, k;
vector<Edge> g[maxn];

// SPFA 在分层图（点 × 余数）上求最短路。
// 状态 (u, r) 表示：到达 u 且到达时刻 mod k = r。
// dist[u][r] 记录该状态的最早真实到达时刻。
void spfa() {
  // 初始化所有状态为 INF
  for (int i = 1; i <= n; ++i)
    for (int j = 0; j < k; ++j)
      dist[i][j] = INF;

  queue<State> q;
  // 入口：0 时刻乘车到达 1 号点，余数为 0
  dist[1][0] = 0;
  q.push({1, 0});
  in_queue[1][0] = true;

  while (!q.empty()) {
    State cur = q.front(); q.pop();
    int u = cur.vertex;
    int r = cur.remainder;
    in_queue[u][r] = false; // 出队标记

    for (int i = 0; i < (int)g[u].size(); ++i) {
      Edge &e = g[u][i];
      long long t = dist[u][r];

      // 如果当前时刻早于道路的开放时间，
      // 不能原地等待，只能把整条路径后移若干个 k（入口巴士推迟）
      if (t < e.open_time) {
        long long diff = e.open_time - t;
        long long p = (diff + k - 1) / k; // 需要推迟几个周期
        t += p * k;
      }

      // 每条道路恰好走 1 单位时间
      long long nt = t + 1;
      int nr = nt % k; // 下一状态的余数

      // 松弛：找到更早的到达时刻才更新
      if (nt >= dist[e.to][nr]) continue;
      dist[e.to][nr] = nt;

      // 如果不在队列中则入队，避免重复
      if (!in_queue[e.to][nr]) {
        q.push({e.to, nr});
        in_queue[e.to][nr] = true;
      }
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int m;
  cin >> n >> m >> k;

  for (int i = 0; i < m; ++i) {
    int u, v, a;
    cin >> u >> v >> a;
    g[u].push_back({v, a});
  }

  spfa();

  if (dist[n][0] == INF) cout << -1 << '\n';
  else cout << dist[n][0] << '\n';

  return 0;
}
