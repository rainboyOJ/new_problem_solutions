/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 11:58
 * update_at: 2026-10-06 11:58
 */

#include <cstdio>

typedef long long ll;

const int MAXM = 10005;

int n, m;
int a[105];
ll f[MAXM]; // f[j] 表示已处理的数中选出若干个、和恰好为 j 的方案数

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);

    // 边界：空集凑出和 0，方案数为 1
    f[0] = 1;
    // 01 背包计数：每个数只有选/不选两种决策，方案数转移是加法
    // j 必须倒序枚举，保证 f[j-x] 还是上一轮的旧值，每个数至多选一次
    for (int i = 1; i <= n; i++)
        for (int j = m; j >= a[i]; j--)
            f[j] += f[j - a[i]];

    printf("%lld\n", f[m]);
    return 0;
}
