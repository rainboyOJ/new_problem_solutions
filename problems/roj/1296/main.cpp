/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 08:10
 * update_at: 2026-10-05 08:10
 */

#include <cstdio>

typedef long long ll;

const int MAXN = 105;

ll n, k;              // 地点数、最小间距限制
ll m[MAXN];           // m[i]: 第 i 个地点的位置（升序）
ll p[MAXN];           // p[i]: 在第 i 个地点开店的利润
ll dp[MAXN];          // dp[i]: 以第 i 个地点作为最后一家店时的最大利润

// 处理一组数据：读入并做线性 DP
void solve() {
    scanf("%lld %lld", &n, &k);
    for (ll i = 1; i <= n; i++) scanf("%lld", &m[i]);
    for (ll i = 1; i <= n; i++) scanf("%lld", &p[i]);

    ll ans = 0;
    // 位置升序，能接在 i 前面的店 j 一定满足 m[i] - m[j] > k
    // 利润都为正，没有合法前驱时 dp[i] 就是 p[i] 自己
    for (ll i = 1; i <= n; i++) {
        dp[i] = p[i];
        for (ll j = 1; j < i; j++)
            if (m[i] - m[j] > k && dp[j] + p[i] > dp[i])
                dp[i] = dp[j] + p[i];
        if (dp[i] > ans) ans = dp[i]; // 答案取所有收尾位置的最大值
    }
    printf("%lld\n", ans);
}

int main() {
    ll T;
    scanf("%lld", &T);
    for (ll t = 1; t <= T; t++) solve();
    return 0;
}
