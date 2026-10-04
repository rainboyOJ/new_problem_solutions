/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 07:39
 * update_at: 2026-10-05 07:39
 */
#include <cstdio>

using namespace std;

typedef long long ll;

const int MAXN = 35;   // 物品种数上限
const int MAXM = 205;  // 背包容量的上限

int n, m;              // n 种物品，背包容量 m
int w[MAXN];           // 第 i 种物品的重量
int c[MAXN];           // 第 i 种物品的价值
int dp[MAXM];          // dp[j] 表示容量不超过 j 时的最大价值

int main() {
    scanf("%d%d", &m, &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &w[i], &c[i]);
    }

    // 完全背包：容量正序枚举，允许同一种物品被多次选取
    for (int i = 1; i <= n; i++) {
        for (int j = w[i]; j <= m; j++) {
            if (dp[j - w[i]] + c[i] > dp[j]) {
                dp[j] = dp[j - w[i]] + c[i];
            }
        }
    }

    printf("max=%d\n", dp[m]);
    return 0;
}
