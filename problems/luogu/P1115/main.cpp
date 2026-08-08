/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-04 12:24
 * update_at: 2026-08-04 12:24
 */

/* P1115 最大子段和 */
/* 一维线性 DP：以 i 结尾的最大子段和只有两种来源——
 * 要么从 a[i] 重新开始，要么接到以 i-1 结尾的最优子段后面。 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;

int n;
int a[MAXN];             // 输入序列
long long dp[MAXN];      // dp[i]：以第 i 个数结尾的最大子段和

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    dp[1] = a[1];              // 边界：第一个数只能自己成一段
    long long ans = dp[1];     // 答案 = 所有结尾里的最大值
    for (int i = 2; i <= n; i++) {
        // 转移：从 i 重新开始，或把 a[i] 接到前一个最优子段后面
        dp[i] = max(1LL * a[i], dp[i - 1] + a[i]);
        ans = max(ans, dp[i]);
    }

    cout << ans << '\n';
    return 0;
}
