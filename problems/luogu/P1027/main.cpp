/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-10 23:22
 * update_at: 2026-11-10 23:22
 */
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

const double INF = 1e18;

struct Point {
    double x, y;
    int city;
};

struct Edge {
    int to;
    double w;
};

// 计算两点之间的欧几里得距离
double dist(const Point& a, const Point& b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}

// 整数距离平方，用于无误差判断直角顶点
long long dist_sq(long long x1, long long y1, long long x2, long long y2) {
    return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
}

void solve() {
    int S, t, A, B;
    if (!(cin >> S >> t >> A >> B)) return;

    vector<Point> pts;
    pts.push_back({0, 0, 0}); // 0 号为超级源点

    vector<double> T(S + 1);

    for (int i = 1; i <= S; ++i) {
        long long x1, y1, x2, y2, x3, y3, cost;
        cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> cost;
        T[i] = cost;

        long long d12 = dist_sq(x1, y1, x2, y2);
        long long d23 = dist_sq(x2, y2, x3, y3);
        long long d13 = dist_sq(x1, y1, x3, y3);

        long long x4 = 0, y4 = 0;
        // 勾股定理确定直角顶点并利用平行四边形定则求第四点
        if (d12 + d13 == d23) {
            // (x1, y1) 为直角
            x4 = x2 + x3 - x1;
            y4 = y2 + y3 - y1;
        } else if (d12 + d23 == d13) {
            // (x2, y2) 为直角
            x4 = x1 + x3 - x2;
            y4 = y1 + y3 - y2;
        } else {
            // (x3, y3) 为直角
            x4 = x1 + x2 - x3;
            y4 = y1 + y2 - y3;
        }

        pts.push_back({static_cast<double>(x1), static_cast<double>(y1), i});
        pts.push_back({static_cast<double>(x2), static_cast<double>(y2), i});
        pts.push_back({static_cast<double>(x3), static_cast<double>(y3), i});
        pts.push_back({static_cast<double>(x4), static_cast<double>(y4), i});
    }

    if (A == B) {
        cout << fixed << setprecision(1) << 0.0 << "\n";
        return;
    }

    int total_nodes = 4 * S;
    vector<vector<Edge>> g(total_nodes + 1);

    // 超级源点连接城市 A 的 4 个机场
    for (int i = 1; i <= 4; ++i) {
        int u = (A - 1) * 4 + i;
        g[0].push_back({u, 0.0});
    }

    // 建立所有机场之间的双向边
    for (int u = 1; u <= total_nodes; ++u) {
        for (int v = u + 1; v <= total_nodes; ++v) {
            double d = dist(pts[u], pts[v]);
            double w = 0;
            if (pts[u].city == pts[v].city) {
                // 同城高铁
                w = d * T[pts[u].city];
            } else {
                // 跨城飞机
                w = d * t;
            }
            g[u].push_back({v, w});
            g[v].push_back({u, w});
        }
    }

    // Dijkstra 最短路
    vector<double> dis(total_nodes + 1, INF);
    using State = pair<double, int>;
    priority_queue<State, vector<State>, greater<State>> pq;

    dis[0] = 0.0;
    pq.push({0.0, 0});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (d > dis[u]) continue;

        for (const auto& e : g[u]) {
            if (dis[u] + e.w < dis[e.to]) {
                dis[e.to] = dis[u] + e.w;
                pq.push({dis[e.to], e.to});
            }
        }
    }

    double ans = INF;
    for (int i = 1; i <= 4; ++i) {
        int v = (B - 1) * 4 + i;
        ans = min(ans, dis[v]);
    }

    cout << fixed << setprecision(1) << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (cin >> n) {
        while (n--) {
            solve();
        }
    }

    return 0;
}
