/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 10:53
 * update_at: 2026-10-06 10:53
 */

#include <cstdio>

typedef long long ll;

// a, b, p 最大 1e18，a*b 会超 long long，只能用龟速乘
ll a, b, p;

// 龟速乘：把 b 按二进制拆成若干 2 的幂之和，用逐位翻倍的加法代替乘法
// 核心是 (x + y) % p = ((x%p) + (y%p)) % p，result 和 a 始终保持 < p，和不超过 2p，不会溢出
ll mod_mul(ll a, ll b, ll p) {
    ll result = 0;      // 已收编二进制位的和，初值 0（加法单位元）
    a %= p;             // a 可能不小于 p，先压回 [0, p)，后面加法才不越界
    while (b) {
        if (b & 1)                  // b 的最低位为 1：这份 a*2^k 加进答案
            result = (result + a) % p;
        a = (a + a) % p;            // a*2^k 翻倍成 a*2^(k+1)，加法代替乘 2
        b >>= 1;                    // 消费下一位
    }
    return result;
}

int main() {
    scanf("%lld%lld%lld", &a, &b, &p);
    printf("%lld\n", mod_mul(a, b, p));
    return 0;
}
