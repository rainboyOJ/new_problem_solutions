/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 09:41
 * update_at: 2026-10-06 09:41
 */

// 完全背包求"凑出每个邮资最少要几张邮票"，从 1 开始数连续可达的邮资个数。
#include <cstdio>

typedef long long ll;

const ll MAXV = 200 * 10000 + 5; // 邮资上界 K * max(面值) + 余量，答案不会超过 K * 最大面值

int k;      // 最多能贴的邮票张数
int n;      // 邮票面值种数
int val[55]; // val[i] = 第 i 种邮票的面值
int f[MAXV]; // f[v] = 凑出邮资 v 所需的最少邮票张数，INF 表示暂时凑不出

const int INF = 0x3f3f3f3f;

int main() {
    scanf("%d %d", &k, &n);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &val[i]);

    int cap = k * 10000; // 每张邮票面值 <= 10000，超过 cap 的邮资一定贴不出，无需计算

    // 完全背包：v 从小到大扫（面值可重复选取），f[v] = 1 + min(f[v - s])
    f[0] = 0;
    for (int v = 1; v <= cap; ++v) {
        f[v] = INF;
        for (int i = 1; i <= n; ++i) {
            int s = val[i];
            if (s <= v && f[v - s] + 1 < f[v])
                f[v] = f[v - s] + 1;
        }
    }

    // 从 1 开始找第一个"最少张数 > k"的邮资，它前面连续可达的个数就是答案
    int ans = 0;
    while (ans + 1 <= cap && f[ans + 1] <= k)
        ++ans;

    printf("%d\n", ans);
    return 0;
}
