/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 13:42
 * update_at: 2026-10-06 13:42
 */

#include <cstdio>
#include <algorithm>

typedef long long ll;

const int MAXN = 1e5 + 5;

int n;
ll a[MAXN]; // 原数列，下标 1..n

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%lld", &a[i]);

    // 差分 b[i] = a[i] - a[i-1]（约定 a[0] = 0）。
    // “所有数相等” <=> b[2..n] 全为 0；b[1] 只决定公共值，是自由槽；
    // 虚拟槽 b[n+1] 也是自由槽，用来吸收后缀区间的另一端。
    // 一次区间 [l, r] ±1 在差分数组上就是 b[l] 与 b[r+1] 一正一反的单点变化。
    ll pos = 0; // b[2..n] 中正数之和：需要被减掉的总缺口
    ll neg = 0; // b[2..n] 中负数绝对值之和：需要被加回来的总缺口
    for (int i = 2; i <= n; ++i) {
        ll d = a[i] - a[i - 1];
        if (d > 0) pos += d;
        else neg -= d;
    }

    // 一正一负槽可在同一次操作中配对各消 1，
    // 剩下的单边缺口 |pos - neg| 用前缀/后缀区间操作甩给自由槽，
    // 所以最少操作次数是 max(pos, neg)。
    printf("%lld\n", std::max(pos, neg));

    // 单边缺口的每一步既可落在 b[1]（公共值 +1）也可落在 b[n+1]（不变），
    // k = |pos - neg| 步里自由分配，公共值可偏移 0..k，共 k+1 种结果。
    printf("%lld\n", (pos > neg ? pos - neg : neg - pos) + 1);

    return 0;
}
