/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 13:35
 * update_at: 2026-10-06 13:35
 */
#include <cstdio>
#include <algorithm>

typedef long long ll;

const int MAXN = 30005; // 总钱数 N < 30000，多开几位防止越界

ll dp[MAXN]; // dp[c] 表示花费不超过 c 时，价格与重要度乘积和的最大值

int main() {
    int budget, m;
    scanf("%d %d", &budget, &m);

    for (int i = 1; i <= m; i++) {
        ll price, weight;
        scanf("%lld %lld", &price, &weight);
        ll gain = price * weight; // 选这件物品获得的乘积值
        // 倒序枚举容量，保证 dp[c - price] 还是上一件物品的结果，每件物品只选一次
        for (int c = budget; c >= price; c--) {
            dp[c] = std::max(dp[c], dp[c - price] + gain);
        }
    }

    printf("%lld\n", dp[budget]);
    return 0;
}
