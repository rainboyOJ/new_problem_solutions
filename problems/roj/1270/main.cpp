/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 07:38
 * update_at: 2026-10-05 07:38
 */
// main.cpp：混合背包，一维滚动数组按物品类型选择正序或倒序更新。
#include <cstdio>

typedef long long ll;

const int MAXM = 205;

ll dp[MAXM]; // dp[j] 表示容量为 j 时能获得的最大价值
ll m, n;     // 背包容量、物品数量

// 01 背包物品：倒序更新，保证 dp[j - w] 是还没选当前物品的旧值
void pack01(ll w, ll c) {
    for (ll j = m; j >= w; j--) {
        if (dp[j - w] + c > dp[j]) {
            dp[j] = dp[j - w] + c;
        }
    }
}

// 完全背包物品：正序更新，允许同一物品被重复选取
void pack_full(ll w, ll c) {
    for (ll j = w; j <= m; j++) {
        if (dp[j - w] + c > dp[j]) {
            dp[j] = dp[j - w] + c;
        }
    }
}

int main() {
    scanf("%lld %lld", &m, &n);
    for (ll i = 1; i <= n; i++) {
        ll w, c, p;
        scanf("%lld %lld %lld", &w, &c, &p);

        if (p == 0) {
            pack_full(w, c); // 无限件
        } else {
            // 有限件：二进制拆成 1,2,4,... 件一组的 01 物品，任意取法都能凑出
            ll k = 1;
            while (k <= p) {
                pack01(k * w, k * c);
                p -= k;
                k = k * 2;
            }
            if (p > 0) {
                pack01(p * w, p * c);
            }
        }
    }
    printf("%lld\n", dp[m]);
    return 0;
}
