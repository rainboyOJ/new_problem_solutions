/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-10 23:22
 * update_at: 2026-11-10 23:22
 */
// brute.cpp：使用 Floyd-Warshall 全源最短路算法作为基准
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

const double INF = 1e18;

struct Point {
    double x, y;
    int city;
};

double dist(const Point& a, const Point& b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}

long long dist_sq(long long x1, long long y1, long long x2, long long y2) {
    return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
}

void solve() {
    int S, t, A, B;
    if (!(cin >> S >> t >> A >> B)) return;

    vector<Point> pts;
    pts.push_back({0, 0, 0});
    vector<double> T(S + 1);

    for (int i = 1; i <= S; ++i) {
        long long x1, y1, x2, y2, x3, y3, cost;
        cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> cost;
        T[i] = cost;

        long long d12 = dist_sq(x1, y1, x2, y2);
        long long d23 = dist_sq(x2, y2, x3, y3);
        long long d13 = dist_sq(x1, y1, x3, y3);

        long long x4 = 0, y4 = 0;
        if (d12 + d13 == d23) {
            x4 = x2 + x3 - x1;
            y4 = y2 + y3 - y1;
        } else if (d12 + d23 == d13) {
            x4 = x1 + x3 - x2;
            y4 = y1 + y3 - y2;
        } else {
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

    int total = 4 * S;
    vector<vector<double>> dis(total + 1, vector<double>(total + 1, INF));

    for (int i = 1; i <= total; ++i) dis[i][i] = 0;

    for (int u = 1; u <= total; ++u) {
        for (int v = u + 1; v <= total; ++v) {
            double d = dist(pts[u], pts[v]);
            double w = 0;
            if (pts[u].city == pts[v].city) {
                w = d * T[pts[u].city];
            } else {
                w = d * t;
            }
            dis[u][v] = dis[v][u] = w;
        }
    }

    // Floyd 三重循环
    for (int k = 1; k <= total; ++k) {
        for (int i = 1; i <= total; ++i) {
            for (int j = 1; j <= total; ++j) {
                if (dis[i][k] + dis[k][j] < dis[i][j]) {
                    dis[i][j] = dis[i][k] + dis[k][j];
                }
            }
        }
    }

    double ans = INF;
    for (int i = 1; i <= 4; ++i) {
        int u = (A - 1) * 4 + i;
        for (int j = 1; j <= 4; ++j) {
            int v = (B - 1) * 4 + j;
            ans = min(ans, dis[u][v]);
        }
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
