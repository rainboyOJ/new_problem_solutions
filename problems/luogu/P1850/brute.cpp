/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-11 01:35
 * update_at: 2026-11-11 01:35
 */

// brute.cpp：小数据下枚举申请集合并精确计算期望
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, v, e;
    if (!(cin >> n >> m >> v >> e)) return 0;
    vector<int> c(n + 1), d(n + 1);
    vector<double> k(n + 1);
    for (int i = 1; i <= n; ++i) cin >> c[i];
    for (int i = 1; i <= n; ++i) cin >> d[i];
    for (int i = 1; i <= n; ++i) cin >> k[i];

    vector<vector<int>> g(v + 1, vector<int>(v + 1, 1e8));
    for (int i = 1; i <= v; ++i) g[i][i] = 0;
    for (int i = 0; i < e; ++i) {
        int u, to, w;
        cin >> u >> to >> w;
        if (w < g[u][to]) g[u][to] = g[to][u] = w;
    }

    for (int p = 1; p <= v; ++p)
        for (int i = 1; i <= v; ++i)
            for (int j = 1; j <= v; ++j)
                if (g[i][p] + g[p][j] < g[i][j])
                    g[i][j] = g[i][p] + g[p][j];

    double min_exp = 1e18;

    // 枚举哪些课程申请更换
    for (int mask = 0; mask < (1 << n); ++mask) {
        if (__builtin_popcount(mask) > m) continue;

        // 计算当前申请集合下的期望路程
        double cur_exp = 0;
        for (int i = 1; i < n; ++i) {
            bool a1 = (mask >> (i - 1)) & 1;
            bool a2 = (mask >> i) & 1;

            double p1 = a1 ? k[i] : 0.0;
            double p2 = a2 ? k[i + 1] : 0.0;

            double term =
                p1 * p2 * g[d[i]][d[i + 1]] +
                p1 * (1.0 - p2) * g[d[i]][c[i + 1]] +
                (1.0 - p1) * p2 * g[c[i]][d[i + 1]] +
                (1.0 - p1) * (1.0 - p2) * g[c[i]][c[i + 1]];

            cur_exp += term;
        }

        min_exp = min(min_exp, cur_exp);
    }

    cout << fixed << setprecision(2) << min_exp << "\n";
    return 0;
}
