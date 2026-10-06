/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 09:51
 * update_at: 2026-10-06 09:51
 */
#include <cstdio>

typedef long long ll;

const int MAXS = 800; // N 最大 39 时总和 N(N+1)/2 = 780，target 最大 390

ll n;
ll dp[MAXS]; // dp[j] 表示从 1..n 中选若干互不相同的数，和恰好为 j 的方案数

int main() {
    scanf("%lld", &n);

    ll sum = n * (n + 1) / 2; // 1..n 的总和

    // 总和为奇数时无法二等分，方案数为 0
    if (sum % 2 == 1) {
        printf("0\n");
        return 0;
    }

    ll target = sum / 2;

    // 0-1 背包计数：dp[0] = 1 表示空集这一种取法
    dp[0] = 1;
    for (ll i = 1; i <= n; i++) {
        // 倒序枚举容量，保证每个数字 i 只被选一次
        for (ll j = target; j >= i; j--) {
            dp[j] += dp[j - i];
        }
    }

    // 每个无序划分 {A, B} 在 dp 中被统计了两次（A 当选中集 / B 当选中集），除以 2
    printf("%lld\n", dp[target] / 2);
    return 0;
}
