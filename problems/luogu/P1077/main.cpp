/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-05 10:40
 * update_at: 2026-08-05 10:55
 */
// 二维 DP：dp[i][j] 表示前 i 种花共摆 j 盆的方案数，直接枚举第 i 种花摆 k 盆。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;
const int MAXM = 105;
const int MOD = 1000007;

int n, m;
int a[MAXN];                // a[i] 表示第 i 种花最多能摆的盆数
long long dp[MAXN][MAXM];   // dp[i][j] 前 i 种花共摆 j 盆的方案数

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];

    // 边界：0 种花只能摆 0 盆，方案数为 1
    dp[0][0] = 1;

    // 前 i 种花共摆 j 盆：枚举第 i 种花摆 k 盆 (0 <= k <= a[i])
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            for (int k = 0; k <= a[i] && k <= j; k++) {
                dp[i][j] += dp[i - 1][j - k];
                dp[i][j] %= MOD;
            }
        }
    }

    cout << dp[n][m] << '\n';

    return 0;
}
