/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-05 10:40
 * update_at: 2026-08-05 10:40
 */
// 二维 DP + 前缀和优化：dp[i][j] 表示前 i 种花共摆 j 盆的方案数，不使用滚动数组。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;
const int MAXM = 105;
const int MOD = 1000007;

int n, m;
int a[MAXN];                 // a[i] 表示第 i 种花最多能摆的盆数
long long dp[MAXN][MAXM];    // dp[i][j] 前 i 种花共摆 j 盆的方案数
long long pre[MAXM];         // 前缀和：pre[j] = dp[i-1][0..j] 的和

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];

    // 边界：0 种花只能摆 0 盆，方案数为 1
    dp[0][0] = 1;

    for (int i = 1; i <= n; i++) {
        // 计算上一行 dp[i-1] 的前缀和
        pre[0] = dp[i - 1][0];
        for (int j = 1; j <= m; j++)
            pre[j] = (pre[j - 1] + dp[i - 1][j]) % MOD;

        // 转移：第 i 种花可以摆 0..a[i] 盆
        for (int j = 0; j <= m; j++) {
            int l = max(0, j - a[i]);   // 第 i 种花最多贡献 a[i] 盆，所以 j 至少从 j-a[i] 取
            long long val = pre[j];
            if (l > 0) val -= pre[l - 1];
            val %= MOD;
            if (val < 0) val += MOD;
            dp[i][j] = val;
        }
    }

    cout << dp[n][m] << '\n';

    return 0;
}
