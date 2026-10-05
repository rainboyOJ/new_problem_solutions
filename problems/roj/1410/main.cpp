/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 23:10
 * update_at: 2026-10-05 23:10
 */
#include <cstdio>
using namespace std;

typedef long long ll;

ll m, n; // 区间左右端点，题目要求对 [m, n] 中每个数求最大质因子

// 返回 x 的最大质因子：从小到大除尽因子，最后剩下的商就是答案
ll largest_prime_factor(ll x) {
    ll factor = 2;
    while (factor * factor <= x) {
        if (x % factor == 0) {
            x /= factor; // 除尽这个因子，剩下的商不含更小的质因子
        } else {
            // 2 之后只试奇数，跳过偶数
            factor += (factor == 2 ? 1 : 2);
        }
    }
    return x; // 循环结束时商本身已是最大质因子（x 为质数时直接返回 x）
}

int main() {
    scanf("%lld %lld", &m, &n);

    // 按 i 从小到大输出每个数的最大质因子，用逗号间隔
    for (ll i = m; i <= n; i++) {
        if (i > m) {
            printf(",");
        }
        printf("%lld", largest_prime_factor(i));
    }
    printf("\n");

    return 0;
}
