/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-11 00:38
 * update_at: 2026-11-11 00:38
 */
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

// 暴力版本：DFS 枚举行 + DFS 枚规律求分值
int n, m, r, c;
int a[20][20];
int sel_r[20], sel_c[20];
int ans = 1e9;

void calc() {
    int sum = 0;
    // 纵向相邻差
    for (int j = 1; j <= c; ++j) {
        for (int i = 1; i < r; ++i) {
            sum += abs(a[sel_r[i]][sel_c[j]] - a[sel_r[i + 1]][sel_c[j]]);
        }
    }
    // 横向相邻差
    for (int i = 1; i <= r; ++i) {
        for (int j = 1; j < c; ++j) {
            sum += abs(a[sel_r[i]][sel_c[j]] - a[sel_r[i]][sel_c[j + 1]]);
        }
    }
    ans = min(ans, sum);
}

void dfs_c(int cur, int cnt) {
    if (cnt == c) {
        calc();
        return;
    }
    if (cur > m || m - cur + 1 < c - cnt) return;
    sel_c[cnt + 1] = cur;
    dfs_c(cur + 1, cnt + 1);
    dfs_c(cur + 1, cnt);
}

void dfs_r(int cur, int cnt) {
    if (cnt == r) {
        dfs_c(1, 0);
        return;
    }
    if (cur > n || n - cur + 1 < r - cnt) return;
    sel_r[cnt + 1] = cur;
    dfs_r(cur + 1, cnt + 1);
    dfs_r(cur + 1, cnt);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> n >> m >> r >> c)) return 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cin >> a[i][j];
        }
    }

    ans = 1e9;
    dfs_r(1, 0);
    cout << ans << "\n";
    return 0;
}
