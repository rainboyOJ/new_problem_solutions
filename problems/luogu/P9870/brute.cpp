/**
 * Problem: luogu P9870 - [NOIP2023] 双序列拓展 (Brute Force DP)
 * Author: rainboy
 * Date: 2026-11-10 23:30
 * Description: 动态规划直接验证网格路径连通性
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 2005;

int n, m;
int a[MAXN], b[MAXN];
int pa[MAXN], va[MAXN], pb[MAXN], vb[MAXN];
bool dp[MAXN][MAXN];

bool solve_dp() {
    if (a[1] == b[1]) return false;
    bool need_less = (a[1] < b[1]);

    if (need_less && a[n] >= b[m]) return false;
    if (!need_less && a[n] <= b[m]) return false;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            dp[i][j] = false;
        }
    }

    dp[1][1] = true;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (!dp[i][j]) continue;

            // 向右拓展 (i, j+1)
            if (j + 1 <= m) {
                bool valid = need_less ? (a[i] < b[j + 1]) : (a[i] > b[j + 1]);
                if (valid) dp[i][j + 1] = true;
            }

            // 向下拓展 (i+1, j)
            if (i + 1 <= n) {
                bool valid = need_less ? (a[i + 1] < b[j]) : (a[i + 1] > b[j]);
                if (valid) dp[i + 1][j] = true;
            }

            // 向右下拓展 (i+1, j+1)
            if (i + 1 <= n && j + 1 <= m) {
                bool valid = need_less ? (a[i + 1] < b[j + 1]) : (a[i + 1] > b[j + 1]);
                if (valid) dp[i + 1][j + 1] = true;
            }
        }
    }

    return dp[n][m];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int c, q;
    if (!(cin >> c >> n >> m >> q)) return 0;

    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= m; ++i) cin >> b[i];

    cout << (solve_dp() ? '1' : '0');

    while (q--) {
        int kx, ky;
        cin >> kx >> ky;
        for (int i = 1; i <= kx; ++i) {
            cin >> pa[i] >> va[i];
            swap(a[pa[i]], va[i]);
        }
        for (int i = 1; i <= ky; ++i) {
            cin >> pb[i] >> vb[i];
            swap(b[pb[i]], vb[i]);
        }

        cout << (solve_dp() ? '1' : '0');

        for (int i = 1; i <= kx; ++i) {
            swap(a[pa[i]], va[i]);
        }
        for (int i = 1; i <= ky; ++i) {
            swap(b[pb[i]], vb[i]);
        }
    }
    cout << "\n";

    return 0;
}
