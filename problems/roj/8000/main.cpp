/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 16:42
 * update_at: 2026-10-06 16:42
 */

// 把所有数变成 0 的最少操作次数：
// 记 P = 正数之和，N = 负数绝对值之和。
// 下界：两类不等式相加得 x + y >= max(P, N)；
// 构造：先配对 min(P, N) 次（正数挪 1 给负数），再单个操作清掉剩余 |P - N|，
// 恰好达到 max(P, N)，所以答案就是 max(P, N)。

#include <cstdio>

typedef long long ll;

const int MAXN = 100005;

int n;
ll a[MAXN]; // a[i] 存第 i 个数

int main() {
    scanf("%d", &n);
    ll pos = 0, neg = 0; // pos = 正数之和 P，neg = 负数绝对值之和 N
    for (int i = 1; i <= n; ++i) {
        scanf("%lld", &a[i]);
        if (a[i] > 0)
            pos += a[i];
        else
            neg += -a[i]; // 负数取绝对值累加（0 也无害）
    }
    // 答案为两者较大值；|a_i| <= 1e5、n <= 1e5，和最大 1e10，必须用 ll
    ll ans = pos > neg ? pos : neg;
    printf("%lld\n", ans);
    return 0;
}
