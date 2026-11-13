/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-13 11:14
 * update_at: 2026-11-13 11:14
 */
#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <algorithm>

using namespace std;

const long long INF = 1e18;
const int maxn = 1005;

struct Edge {
    int to;
    long long w;
};

vector<Edge> g[maxn];
long long s[maxn];

// dist[u][b] 表示当前人在城市 u，手里骑着在城市 b 购买的自行车时的最短耗时
long long dist_city[maxn][maxn];

void solve() {
    int n, m;
    if (!(cin >> n >> m)) return;

    for (int i = 1; i <= n; ++i) {
        g[i].clear();
        for (int j = 1; j <= n; ++j) {
            dist_city[i][j] = INF;
        }
    }

    for (int i = 0; i < m; ++i) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }

    for (int i = 1; i <= n; ++i) {
        cin >> s[i];
    }

    // 优先队列小顶堆：存储 (耗时 d, 当前城市 u, 自行车归属城市 b)
    priority_queue<tuple<long long, int, int>, vector<tuple<long long, int, int>>, greater<tuple<long long, int, int>>> pq;

    // 起点初始化：必须且只能在城市 1 购买自行车
    dist_city[1][1] = 0;
    pq.push({0, 1, 1});

    while (!pq.empty()) {
        auto [d, u, b] = pq.top();
        pq.pop();

        if (d > dist_city[u][b]) continue;

        // 动作 1：垂直层间转移（换车降落）
        // 若当前城市 u 出售的自行车比手里现有的更快（s[u] < s[b]），耗时 0 降落至新车对应的层
        if (s[u] < s[b]) {
            if (dist_city[u][u] > d) {
                dist_city[u][u] = d;
                pq.push({d, u, u});
            }
        }

        // 动作 2：层内平移赶路（保持手里的车向前开）
        long long cur_speed = s[b];
        for (const auto& edge : g[u]) {
            int v = edge.to;
            long long w = edge.w;
            long long cost = d + w * cur_speed;

            if (dist_city[v][b] > cost) {
                dist_city[v][b] = cost;
                pq.push({cost, v, b});
            }
        }
    }

    // 在所有可能的最终车辆层中，取到达城市 n 的最小耗时
    long long ans = INF;
    for (int b = 1; b <= n; ++b) {
        ans = min(ans, dist_city[n][b]);
    }

    cout << ans << "\n";
}

int main() {
    // 提升标准流性能
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}
