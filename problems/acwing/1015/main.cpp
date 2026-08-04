/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-04 12:40
 * update_at: 2026-08-04 12:40
 */

/* AcWing 1015 摘花生 */
/* 网格路径 DP：从 (1,1) 只能向右/向下走到 (R,C)，每个格子只能从上方或左方走来，
 * dp[i][j] = max(dp[i-1][j], dp[i][j-1]) + a[i][j]。 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;

int t;                    // 测试组数
int r, c;                 // 花生地行数、列数
int a[MAXN][MAXN];        // a[i][j]：位置 (i, j) 的花生数量
int dp[MAXN][MAXN];       // dp[i][j]：从 (1,1) 走到 (i,j) 能摘到的最大花生数

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> t;
    while (t--) {
        cin >> r >> c;
        for (int i = 1; i <= r; i++) {
            for (int j = 1; j <= c; j++) {
                cin >> a[i][j];
            }
        }

        // 起点边界：只有它自己
        dp[1][1] = a[1][1];
        for (int i = 1; i <= r; i++) {
            for (int j = 1; j <= c; j++) {
                if (i == 1 && j == 1)
                    continue;
                // 从上方或左方走来，取较大者，再加上当前位置的花生
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]) + a[i][j];
            }
        }

        cout << dp[r][c] << '\n';
    }
    return 0;
}
