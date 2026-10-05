/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 00:35
 * update_at: 2026-10-06 00:35
 */
#include <cstdio>
using namespace std;

typedef long long ll;

// 快速幂：计算 base^exp mod mod，用于费马小定理求逆元
ll fast_pow(ll base, ll exp, ll mod) {
    ll res = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) res = res * base % mod;
        base = base * base % mod;
        exp >>= 1;
    }
    return res;
}

// 计算单步组合数 C(n, m) mod p，要求 n, m < p 且 p 为质数
ll comb_small(ll n, ll m, ll p) {
    if (m < 0 || m > n) return 0;
    if (m > n - m) m = n - m; // 取较小的一侧，减少连乘项数
    ll num = 1; // 分子 (n-m+1) * ... * n
    ll den = 1; // 分母 1 * ... * m
    for (ll i = 1; i <= m; i++) {
        num = num * ((n - m + i) % p) % p;
        den = den * (i % p) % p;
    }
    // 分母与 p 互质（p 为质数且 p > m），用费马小定理求逆元
    return num * fast_pow(den, p - 2, p) % p;
}

// Lucas 定理：把 n, m 按 p 进制逐位拆开，各位小组合数相乘
ll lucas(ll n, ll m, ll p) {
    ll ans = 1;
    while (n > 0 || m > 0) {
        ans = ans * comb_small(n % p, m % p, p) % p;
        if (ans == 0) return 0; // 某一位出现 C(a_i, b_i) = 0，整体即为 0
        n /= p;
        m /= p;
    }
    return ans;
}

int main() {
    ll T;
    scanf("%lld", &T);
    while (T--) {
        ll n, m, p;
        scanf("%lld %lld %lld", &n, &m, &p);
        printf("%lld\n", lucas(n, m, p));
    }
    return 0;
}
