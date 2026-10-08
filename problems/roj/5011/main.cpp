/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-08 15:02
 * update_at: 2026-10-08 15:03
 */
// 一本通 1675《塔》
// 一串相邻合并 => 最终塔列是原序列的一个划分，每座塔 = 一个连续区间的和，
// 操作次数 = N - 段数，所以问题化为「使段和不下降的划分中段数最多」。
//
// 贪心 DP：dp[i] = 前 i 座塔合法划分时「最后一段和」的最小值，g[i] 为对应最多段数。
// 转移来源 j：要求 sum[i]-sum[j] >= dp[j]。因为 A_i>=1 时前缀和严格递增，
// j 从 i-1 往 0 走时段和 sum[i]-sum[j] 单调变大，第一个合法的 j 就给出最小段和。
#include <cstdio>

typedef long long ll;

const int MAXN = 3005;  // N, A_i <= 3000

int n;
ll pre[MAXN];   // pre[i]：前 i 座塔的高度和
ll dp[MAXN];    // dp[i]：前 i 座塔合法划分（段和不降）时，最后一段和的最小值
int g[MAXN];    // g[i]：取到 dp[i] 时的最多段数

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        ll h;
        scanf("%lld", &h);
        pre[i] = pre[i - 1] + h;
    }
    dp[0] = 0;
    g[0] = 0;
    for (int i = 1; i <= n; i++) {
        // 倒序枚举断点 j，第一个合法 j 的段和最小（j=0 恒合法，故转移必定存在）
        for (int j = i - 1; j >= 0; j--) {
            if (pre[i] - pre[j] >= dp[j]) {
                dp[i] = pre[i] - pre[j];
                g[i] = g[j] + 1;
                break;
            }
        }
    }
    printf("%d\n", n - g[n]);
    return 0;
}
