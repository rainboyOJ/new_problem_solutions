/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 00:11
 * update_at: 2026-10-05 00:11
 */

#include <cstdio>

typedef long long ll;

ll k;      // 要求的项数，1 <= k <= 46
ll a, b;   // 滚动窗口：递推中依次保存最近两项 F(i-2)、F(i-1)

int main() {
    scanf("%lld", &k);

    // 前 1、2 项都为 1，无需递推
    if (k <= 2) {
        printf("1\n");
        return 0;
    }

    a = 1; // F(1)
    b = 1; // F(2)

    // 从第 3 项推到第 k 项：每次 t = F(i-1) + F(i-2)，窗口右移一位
    for (ll i = 3; i <= k; ++i) {
        ll t = a + b;
        a = b;
        b = t;
    }

    printf("%lld\n", b);
    return 0;
}
