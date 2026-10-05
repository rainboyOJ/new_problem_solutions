/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 08:04
 * update_at: 2026-10-05 08:04
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;

typedef long long ll;

ll T;               // 数据组数
ll R, C;            // 花生地的行数、列数
ll m[MAXN][MAXN];   // m[i][j]：格子 (i, j) 上的花生数
ll dp[MAXN];        // 一维滚动数组：更新到 dp[j] 前，dp[j] 是上一行的答案（来自上方），dp[j-1] 是本行左边的答案

// 读取一组花生地，并把 dp 数组清成"虚拟第 0 行"（全 0，网格外收获为 0）。
void read_input() {
    cin >> R >> C;
    for (ll i = 1; i <= R; i++) {
        for (ll j = 1; j <= C; j++) {
            cin >> m[i][j];
        }
    }
    for (ll j = 1; j <= C; j++) dp[j] = 0;
}

// 网格 DP：只能向东、向南走，dp[i][j] = m[i][j] + max(上方 dp, 左方 dp)。
// 首行只能从左方来、首列只能从上方来，边界全 0 后转移式自动覆盖，不用单独处理。
void solve() {
    for (ll i = 1; i <= R; i++) {
        for (ll j = 1; j <= C; j++) {
            ll best = dp[j]; // 来自上方
            if (j > 1 && dp[j - 1] > best) best = dp[j - 1]; // 来自左方
            dp[j] = best + m[i][j];
        }
    }
    cout << dp[C] << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> T;
    while (T--) {
        read_input();
        solve();
    }

    return 0;
}
