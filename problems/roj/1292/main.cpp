/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 08:18
 * update_at: 2026-10-05 08:18
 */

/*
 * 二维费用 0/1 背包：
 * 每只小精灵价值为 1，花费是（精灵球数 v，体力伤害 u）。
 * 体力上限是 M-1：题面要求体力降到 0 或以下时狩猎结束，
 * 那只小精灵也收服不了，所以伤害总和必须 < M。
 */
#include <cstdio>

typedef long long ll;

const int MAXN = 1005; // 精灵球数量上限
const int MAXM = 505;  // 皮卡丘体力上限

int n, m, k;           // 精灵球数、初始体力、小精灵只数
int dp[MAXN][MAXM];    // dp[j][p]：球数 <= j、伤害 <= p 时最多收服几只

int main() {
    scanf("%d %d %d", &n, &m, &k);
    int hp_cap = m - 1; // 伤害总和必须 < m，伤害维只开到 m-1

    for (int i = 1; i <= k; ++i) {
        int v, u; // 收服这只需要的精灵球数、对皮卡丘的伤害
        scanf("%d %d", &v, &u);
        if (v > n || u > hp_cap) continue; // 这一只无论如何都收服不了

        // 两个维度都要倒序：正序会让同一只小精灵被重复收服（变成完全背包）
        for (int j = n; j >= v; --j)
            for (int p = hp_cap; p >= u; --p)
                if (dp[j - v][p - u] + 1 > dp[j][p])
                    dp[j][p] = dp[j - v][p - u] + 1;
    }

    // 第一答案：最多收服数量
    int best = dp[n][hp_cap];

    // 次答案：dp[n][p] 随 p 单调不减，首个达到 best 的 p 就是最小伤害
    int min_hp = 0;
    for (int p = 0; p <= hp_cap; ++p)
        if (dp[n][p] == best) {
            min_hp = p;
            break;
        }

    printf("%d %d\n", best, m - min_hp);
    return 0;
}
