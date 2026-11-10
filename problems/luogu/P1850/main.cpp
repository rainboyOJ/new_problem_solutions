/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-11 01:35
 * update_at: 2026-11-11 01:35
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

const double INF = 1e18;
const int MAXN = 2005;
const int MAXV = 305;

int c[MAXN], d[MAXN];
double k_prob[MAXN];
int dist_map[MAXV][MAXV];

// dp[i][j][0/1] 表示前 i 节课，申请了 j 次，第 i 节课 未申请(0)/申请(1) 的最小期望耗费
double dp[MAXN][MAXN][2];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, v, e;
    if (!(cin >> n >> m >> v >> e)) return 0;

    for (int i = 1; i <= n; ++i) cin >> c[i];
    for (int i = 1; i <= n; ++i) cin >> d[i];
    for (int i = 1; i <= n; ++i) cin >> k_prob[i];

    // 初始化全源距离
    for (int i = 1; i <= v; ++i) {
        for (int j = 1; j <= v; ++j) {
            dist_map[i][j] = (i == j ? 0 : 1e8);
        }
    }

    for (int i = 0; i < e; ++i) {
        int u, w_to, w;
        cin >> u >> w_to >> w;
        if (w < dist_map[u][w_to]) {
            dist_map[u][w_to] = dist_map[w_to][u] = w;
        }
    }

    // Floyd 算法求全源最短路
    for (int p = 1; p <= v; ++p) {
        for (int i = 1; i <= v; ++i) {
            for (int j = 1; j <= v; ++j) {
                if (dist_map[i][p] + dist_map[p][j] < dist_map[i][j]) {
                    dist_map[i][j] = dist_map[i][p] + dist_map[p][j];
                }
            }
        }
    }

    // 初始化 DP 数组为极大值
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            dp[i][j][0] = INF;
            dp[i][j][1] = INF;
        }
    }

    // 初始状态：第 1 节课耗费为 0
    dp[1][0][0] = 0;
    if (m >= 1) {
        dp[1][1][1] = 0;
    }

    for (int i = 2; i <= n; ++i) {
        for (int j = 0; j <= min(i, m); ++j) {
            // 1. 第 i 节课不申请：必在 c[i]
            // 来自 i-1 节未申请 (在 c[i-1])
            double from_0 = dp[i - 1][j][0] + dist_map[c[i - 1]][c[i]];

            // 来自 i-1 节申请了 (k[i-1] 在 d[i-1]，1-k[i-1] 在 c[i-1])
            double from_1 = dp[i - 1][j][1] +
                            k_prob[i - 1] * dist_map[d[i - 1]][c[i]] +
                            (1.0 - k_prob[i - 1]) * dist_map[c[i - 1]][c[i]];

            dp[i][j][0] = min(from_0, from_1);

            // 2. 第 i 节课申请：需要 j >= 1
            if (j >= 1) {
                // 来自 i-1 节未申请 (在 c[i-1])
                double apply_from_0 = dp[i - 1][j - 1][0] +
                                     k_prob[i] * dist_map[c[i - 1]][d[i]] +
                                     (1.0 - k_prob[i]) * dist_map[c[i - 1]][c[i]];

                // 来自 i-1 节申请了 (4 种概率组合)
                double apply_from_1 = dp[i - 1][j - 1][1] +
                    k_prob[i - 1] * k_prob[i] * dist_map[d[i - 1]][d[i]] +
                    k_prob[i - 1] * (1.0 - k_prob[i]) * dist_map[d[i - 1]][c[i]] +
                    (1.0 - k_prob[i - 1]) * k_prob[i] * dist_map[c[i - 1]][d[i]] +
                    (1.0 - k_prob[i - 1]) * (1.0 - k_prob[i]) * dist_map[c[i - 1]][c[i]];

                dp[i][j][1] = min(apply_from_0, apply_from_1);
            }
        }
    }

    double ans = INF;
    for (int j = 0; j <= m; ++j) {
        ans = min(ans, min(dp[n][j][0], dp[n][j][1]));
    }

    cout << fixed << setprecision(2) << ans << "\n";

    return 0;
}
