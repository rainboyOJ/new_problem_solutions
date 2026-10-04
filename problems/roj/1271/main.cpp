/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 23:37
 * update_at: 2026-10-04 23:37
 */
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

typedef long long ll;

const int MAXM = 21;  // 需要的氧气量上界
const int MAXN = 79;  // 需要的氮气量上界
const int MAXK = 1005;

// dp[i][j]：需求收拢状态 (i, j)（氧气 min(实际, m)、氮气 min(实际, n)）的最小总重
// 需求是"至少"语义，超过需求的气量不再区分，状态规模只有 (m+1)*(n+1)
// 最大总重 1000*800=8e5，int 足够；memset 0x3f 即为不可达哨兵
int dp[MAXM + 1][MAXN + 1];

ll need_o, need_n;           // 题目要求的氧、氮量，同时是状态表的两个维度
ll k;                        // 气缸个数
ll oxygen[MAXK], nitro[MAXK], weight[MAXK];  // 每个气缸的氧量、氮量、重量

// 放入第 cur 个气缸的 0/1 转移
// 目标下标 (min(i+a, m), min(j+b, n)) 不小于当前下标 (i, j)，
// 所以 i、j 都从大到小枚举：目标状态先写、当前状态后读，
// 本轮新写入的值不会被再次读到，每个气缸至多用一次（0/1 背包）
void pack(int cur) {
    for (ll i = need_o; i >= 0; --i) {
        ll ni = min(i + oxygen[cur], need_o);  // 氧气收拢：超出需求记为 need_o
        for (ll j = need_n; j >= 0; --j) {
            ll nj = min(j + nitro[cur], need_n);  // 氮气收拢：超出需求记为 need_n
            ll cost = dp[i][j] + weight[cur];
            if (cost < dp[ni][nj])
                dp[ni][nj] = cost;
        }
    }
}

int main() {
    scanf("%lld %lld", &need_o, &need_n);
    scanf("%lld", &k);
    for (int i = 1; i <= k; ++i)
        scanf("%lld %lld %lld", &oxygen[i], &nitro[i], &weight[i]);

    memset(dp, 0x3f, sizeof(dp));  // 不可达哨兵；最大总重 1000*800=8e5 远小于 0x3f3f3f3f
    dp[0][0] = 0;  // 什么都不带：两种气体均为 0，总重 0

    for (int i = 1; i <= k; ++i)
        pack(i);

    printf("%d\n", dp[need_o][need_n]);
    return 0;
}
