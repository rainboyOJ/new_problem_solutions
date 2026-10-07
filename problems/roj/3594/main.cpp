/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 14:54
 * update_at: 2026-10-06 14:54
 */
#include <cstdio>

typedef long long ll;

ll n; // 题目给的数，n = p * q（p < q，均为质数）

int main() {
    scanf("%lld", &n);
    // 从小到大试除：第一个能整除 n 的 d 一定是最小质因数 p，
    // 且 p <= sqrt(n) < q，所以商 n / d 就是较大的质数 q
    for (ll d = 2; d * d <= n; d++) {
        if (n % d == 0) {
            printf("%lld\n", n / d);
            return 0;
        }
    }
    // 题目保证 n 是两个不同质数之积，不会走到这里
    return 0;
}
