// main.cpp：时限 2N-1 恰好等于单调路径的格子数，退化为只能向右/向下的网格 DP，滚动数组 O(N^2)。
/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 08:02
 * update_at: 2026-10-05 08:02
 */

#include <cstdio>

typedef long long ll;

const int MAXN = 105;

int n;
int a[MAXN][MAXN]; // a[i][j]：经过格子 (i,j) 要缴的费用，值域 <= 100，用 int 控制内存
ll dp[MAXN];       // dp[j]：滚到当前行时，走到本行第 j 列的最少累计费用

// 从 (1,1) 走到 (n,n)，只能向右或向下，求经过格子（含起终点）的最小费用和。
void solve() {
    // 第一行只能从左边走过来，前缀和即最小费用
    dp[1] = a[1][1];
    for (int j = 2; j <= n; ++j)
        dp[j] = dp[j - 1] + a[1][j];

    // 其余行滚动更新：更新前 dp[j] 是上方值，dp[j-1] 已是本行左方值
    for (int i = 2; i <= n; ++i) {
        dp[1] += a[i][1]; // 第一列只能从上方来
        for (int j = 2; j <= n; ++j) {
            ll best = dp[j]; // 从上方 (i-1,j) 来
            if (dp[j - 1] < best)
                best = dp[j - 1]; // 从左方 (i,j-1) 来
            dp[j] = best + a[i][j];
        }
    }

    printf("%lld\n", dp[n]);
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            scanf("%d", &a[i][j]);
    solve();
    return 0;
}
