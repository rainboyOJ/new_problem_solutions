/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-13 13:20
 * update_at: 2026-08-13 13:20
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 16;        // n <= 15，数组下标从 1 开始
const double INF = 1e100;   // 足够大的数，作为“不可达”

int n;
double x[MAXN], y[MAXN];         // 每块奶酪的坐标，从 1 开始编号
double dis0[MAXN];               // dis0[i]：原点到第 i 块奶酪的距离
double dis[MAXN][MAXN];          // dis[i][j]：第 i 块到第 j 块奶酪的距离
double dp[1 << 15][MAXN];        // dp[mask][u]：已吃集合为 mask 且最后停在 u 的最短距离

// 两点之间的欧氏距离。
double dist(double x1, double y1, double x2, double y2) {
    double dx = x1 - x2;
    double dy = y1 - y2;
    return sqrt(dx * dx + dy * dy);
}

void solve() {
    int full = 1 << n;

    // 先把所有状态初始化为不可达
    for (int mask = 0; mask < full; mask++) {
        for (int i = 1; i <= n; i++) {
            dp[mask][i] = INF;
        }
    }

    // 初始状态：从原点 (0,0) 直接走到第 i 块奶酪
    for (int i = 1; i <= n; i++) {
        dp[1 << (i - 1)][i] = dis0[i];
    }

    // 状态转移：从 dp[mask][u] 走向还没吃的奶酪 v
    for (int mask = 0; mask < full; mask++) {
        for (int u = 1; u <= n; u++) {
            if (dp[mask][u] >= INF / 2) {
                continue;   // 该状态不可达
            }
            for (int v = 1; v <= n; v++) {
                if (mask & (1 << (v - 1))) {
                    continue;   // v 已经吃过了
                }
                int nmask = mask | (1 << (v - 1));
                dp[nmask][v] = min(dp[nmask][v], dp[mask][u] + dis[u][v]);
            }
        }
    }

    // 答案：吃完全部奶酪（mask = full-1）后，最后停在哪一块都行
    double ans = INF;
    for (int i = 1; i <= n; i++) {
        ans = min(ans, dp[full - 1][i]);
    }

    cout.setf(ios::fixed);
    cout << setprecision(2) << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> x[i] >> y[i];
    }

    // 预处理距离：原点到每块奶酪、任意两块奶酪之间
    for (int i = 1; i <= n; i++) {
        dis0[i] = dist(0, 0, x[i], y[i]);
        for (int j = 1; j <= n; j++) {
            dis[i][j] = dist(x[i], y[i], x[j], y[j]);
        }
    }

    solve();

    return 0;
}
