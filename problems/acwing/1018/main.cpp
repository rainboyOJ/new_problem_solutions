/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-04 12:50
 * update_at: 2026-08-04 12:50
 */

/* AcWing 1018 最低通行费 */
/* 2N-1 步穿越 N×N 网格 ⇔ 只能向右/向下走（无绕路余地），
 * 网格 DP 求最小费用：dp[i][j] = min(dp[i-1][j], dp[i][j-1]) + a[i][j]。 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;
const int INF = 0x3f3f3f3f;

int n;                 // 网格边长
int a[MAXN][MAXN];     // a[i][j]：格子 (i,j) 的费用
int dp[MAXN][MAXN];    // dp[i][j]：从 (1,1) 到 (i,j) 的最小费用

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> a[i][j];
        }
    }

    // 起点边界；其余格子先置 INF，保证越界来源（dp[0][j]、dp[i][0]）不会被选中
    memset(dp, 0x3f, sizeof(dp));
    dp[1][1] = a[1][1];
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == 1 && j == 1)
                continue;
            // 从上方或左方走来，取费用较小者（越界来源是 INF，自然被排除）
            dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + a[i][j];
        }
    }

    cout << dp[n][n] << '\n';
    return 0;
}
