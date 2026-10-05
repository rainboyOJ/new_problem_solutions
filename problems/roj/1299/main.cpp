/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 08:25
 * update_at: 2026-10-05 08:25
 */

/*
 * 同余 0/1 背包：
 * dp[j] 表示已选糖果总数模 K 余 j 时的最大总数。
 * 每件糖果只有“不取”和“取”两种去向。余数转移是环形的（会回绕），
 * 所以每处理一件糖果都先把旧表整体快照，再从 old 转移，保证 0/1 语义。
 */
#include <cstdio>

typedef long long ll;

const int MAXK = 105;
const ll NEG = -(1LL << 60); // 不可达哨兵：最大合法总和仅 10^8，叠一件糖果后仍远小于 0

ll n, k;      // 糖果件数、要求整除的模数
ll dp[MAXK];  // dp[j]：总数模 k 余 j 时的最大总数，NEG 表示该余数暂时凑不出
ll old[MAXK]; // 处理当前糖果前的旧表快照

int main() {
    scanf("%lld %lld", &n, &k);

    dp[0] = 0; // 一件都不取：总和 0，余数 0 可达
    for (ll j = 1; j < k; ++j) dp[j] = NEG;

    for (ll i = 1; i <= n; ++i) {
        ll value;
        scanf("%lld", &value);
        ll r = value % k; // 这件糖果对余数的贡献

        for (ll j = 0; j < k; ++j) old[j] = dp[j]; // 快照，只允许从上一件状态转移

        for (ll j = 0; j < k; ++j) {
            ll from = (j - r + k) % k; // 取这件后余数由 from 回绕到 j
            if (old[from] == NEG) continue;
            if (old[from] + value > dp[j]) dp[j] = old[from] + value;
        }
    }

    // dp[0] >= 0（空集），凑不出 k 的倍数时恰好就是 0，无需额外判断
    printf("%lld\n", dp[0]);
    return 0;
}
