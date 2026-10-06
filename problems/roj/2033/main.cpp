/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 09:59
 * update_at: 2026-10-06 09:59
 */

#include <cstdio>

typedef long long ll;

const int MAXN = 10005; // 金额上限 10000

int v, n; // v 种面值，目标金额 n
int coin[30]; // coin[i] 第 i 种货币的面值
ll ways[MAXN]; // ways[j] 表示用已处理过的面值凑出金额 j 的方案数

int main() {
    scanf("%d %d", &v, &n);
    for (int i = 1; i <= v; ++i)
        scanf("%d", &coin[i]);

    // 完全背包计数：外层按面值分组，保证同一种方案的货币顺序不重复计数
    ways[0] = 1; // 金额 0：什么都不取，恰好一种方案
    for (int i = 1; i <= v; ++i)
        for (int j = coin[i]; j <= n; ++j) // 金额正序：ways[j-c] 已含本轮值，同一面值可重复选
            ways[j] += ways[j - coin[i]];

    printf("%lld\n", ways[n]);
    return 0;
}
