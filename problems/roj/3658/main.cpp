/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 16:14
 * update_at: 2026-10-06 16:14
 */

#include <cstdio>

typedef long long ll;

const int MAXN = 1e5 + 5;

int n;
ll d[MAXN]; // d[i] 表示第 i 天的道路深度

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%lld", &d[i]);

    // 每次操作填平一个区间，把"竖直视角"看成铺横条：
    // 只有比左邻高出来的层必须以 i 为左端点新开一次操作，
    // 答案 = sum(max(d[i] - d[i-1], 0))，约定 d[0] = 0。
    ll ans = 0;
    for (int i = 1; i <= n; ++i)
        if (d[i] > d[i - 1])
            ans += d[i] - d[i - 1];

    printf("%lld\n", ans);
    return 0;
}
