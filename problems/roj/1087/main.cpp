/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 00:39
 * update_at: 2026-10-05 00:39
 */

#include <cstdio>

typedef long long ll;

// 调和级数单调递增，逐项累加，首次超过 k 的 n 就是最小答案
int main() {
    ll k;              // 阈值 1 <= k <= 15
    double total = 0;  // 累计的调和级数和 S_n

    scanf("%lld", &k);

    ll n = 0;          // 已累加的项数
    while (total <= k) {
        n++;
        total += 1.0 / (double)n; // 加上第 n 项 1/n
    }

    printf("%lld\n", n);
    return 0;
}
