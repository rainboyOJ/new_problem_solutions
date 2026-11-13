/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-13 12:20
 * update_at: 2026-11-13 12:20
 */
// brute.cpp：基于速度系数为状态的分层图 Dijkstra 对照解法
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
long long dist_val[maxn][maxn];

void solve() {
    int n, m;
    if (!(cin >> n >> m)) return;

    for (int i = 1; i <= n; ++i) {
        g[i].clear();
        for (int k = 1; k <= 1000; ++k) {
            dist_val[i][k] = INF;
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

    // 优先队列小顶堆：(d, u, k)
    priority_queue<tuple<long long, int, int>, vector<tuple<long long, int, int>>, greater<tuple<long long, int, int>>> pq;

    dist_val[1][s[1]] = 0;
    pq.push({0, 1, s[1]});

    while (!pq.empty()) {
        auto [d, u, k] = pq.top();
        pq.pop();

        if (d > dist_val[u][k]) continue;

        // 如果在当前城市有更快的车，原地换车
        int best_k = min((long long)k, s[u]);
        if (dist_val[u][best_k] > d) {
            dist_val[u][best_k] = d;
            pq.push({d, u, best_k});
        }

        for (const auto& edge : g[u]) {
            int v = edge.to;
            long long w = edge.w;

            // 骑着 best_k 前往邻居
            long long nxt_d = d + w * best_k;
            if (dist_val[v][best_k] > nxt_d) {
                dist_val[v][best_k] = nxt_d;
                pq.push({nxt_d, v, best_k});
            }
        }
    }

    long long ans = INF;
    for (int k = 1; k <= 1000; ++k) {
        ans = min(ans, dist_val[n][k]);
    }
    cout << ans << "\n";
}

int main() {
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
