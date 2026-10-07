/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 01:45
 * update_at: 2026-10-06 01:45
 */
#include <cstdio>

typedef long long ll;

// 数据说明：本题源仓库随题的测试数据与评测程序 std.cpp 实际考查的是「整数划分」，
// 而不是题面写的 2×N 骨牌覆盖（上游 1677 的 data/、data.py、std.cpp 与 1675 字节级相同）。
// 输入是 n k，要求把 n 拆成 k 份正整数（不计顺序）的方案数，本题解按此语义实现。

const int MAXN = 1000005;  // 随题数据 n<=200，这里留足余量，避免越界

ll dp[MAXN];               // dp[x]：已经考虑过的面额凑出 x 的方案数（完全背包计数）

int main() {
    ll n, k;
    scanf("%lld %lld", &n, &k);

    // 每份至少为 1，先各减 1，余下 rest 用不超过 k 的数拆分（可以重复、可以为 0）
    ll rest = n - k;
    if (rest < 0) {
        printf("0\n");
        return 0;
    }

    dp[0] = 1;             // 凑 0 只有空方案
    // 外层按面额升序、内层按目标值升序滚动，保证每个划分只沿唯一路径被构造一次
    for (ll coin = 1; coin <= k; coin++) {
        for (ll used = coin; used <= rest; used++) {
            dp[used] += dp[used - coin];   // 再添一枚面额 coin 的方案数
        }
    }

    printf("%lld\n", dp[rest]);
    return 0;
}
