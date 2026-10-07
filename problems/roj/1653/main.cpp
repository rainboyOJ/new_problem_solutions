/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 00:42
 * update_at: 2026-10-06 00:42
 */
#include <cstdio>

typedef long long ll;

const int MOD_G = 1000;        // g(x) = x^x 对 1000 取模
const int BASE = 1000000000;   // 高精度每段保存 9 位十进制数
const int MAXD = 64;           // C(998, 99) 约 139 位十进制，64 段足够

ll big[MAXD]; // 高精度数，从低位到高位每段压 9 位，big[0] 为最低段
ll big_len;   // 当前占用的段数

// 计算 (base^exp) mod mod，用二进制快速幂，只保留低位常数。
ll power_mod(ll base, ll exp, ll mod) {
    ll res = 1 % mod;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) {
            res = res * base % mod;
        }
        base = base * base % mod;
        exp >>= 1;
    }
    return res;
}

// 高精度数乘以一个较小整数 mult（mult 不超过 1000），结果原地保存在 big[]。
void big_mul_small(ll mult) {
    ll carry = 0;
    for (ll i = 0; i < big_len; i++) {
        ll cur = big[i] * mult + carry;
        big[i] = cur % BASE;
        carry = cur / BASE;
    }
    while (carry > 0) {
        big[big_len] = carry % BASE;
        carry /= BASE;
        big_len++;
    }
}

// 高精度数整除一个较小整数 divisor（divisor 不超过 100），结果原地保存在 big[]。
void big_div_small(ll divisor) {
    ll rem = 0;
    for (ll i = big_len - 1; i >= 0; i--) {
        ll cur = rem * BASE + big[i];
        big[i] = cur / divisor;
        rem = cur % divisor;
    }
    while (big_len > 1 && big[big_len - 1] == 0) {
        big_len--;
    }
}

// 求组合数 C(M, K)。逐步用 C(M-K+i, i) = C(M-K+i-1, i-1) * (M-K+i) / i 递推，
// 每一步都是整数，避免先算阶乘再做大数除法。
void combination(ll M, ll K) {
    big[0] = 1;
    big_len = 1;
    for (ll i = 1; i <= K; i++) {
        big_mul_small(M - K + i);
        big_div_small(i);
    }
}

// 按高位到低位输出高精度数，低位段补足 9 位前导零。
void print_big() {
    printf("%lld", big[big_len - 1]);
    for (ll i = big_len - 2; i >= 0; i--) {
        printf("%09lld", big[i]);
    }
    printf("\n");
}

int main() {
    ll k, x;
    scanf("%lld %lld", &k, &x);

    // 第一步：常数项 g(x) = x^x mod 1000。
    ll g = power_mod(x, x, MOD_G);

    // 第二步：隔板法，a1+...+ak = g(x) 的正整数解组数为 C(g(x)-1, k-1)。
    combination(g - 1, k - 1);
    print_big();
    return 0;
}
