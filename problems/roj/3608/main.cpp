/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 15:06
 * update_at: 2026-10-06 15:06
 */
#include <cstdio>

typedef long long ll;

// 快速幂：求 base^exp mod mod，指数按二进制拆分，每次底数平方、指数减半，O(log exp)
ll fast_pow(ll base, ll exp, ll mod) {
    ll result = 1 % mod;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) {
            result = result * base % mod;
        }
        base = base * base % mod;
        exp >>= 1;
    }
    return result;
}

int main() {
    ll n, m, k, x;
    scanf("%lld%lld%lld%lld", &n, &m, &k, &x);
    // 每轮所有人整体顺时针平移 m 格，10^k 轮共平移 m*10^k 格
    // 位置只在 0..n-1 循环，故只需 10^k mod n
    ll step = fast_pow(10, k, n);
    printf("%lld\n", (x + m * step) % n);
    return 0;
}
