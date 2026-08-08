/**
 * P1593 因子和
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */

#include <bits/stdc++.h>
using namespace std;

const int MOD = 9901;

// 快速幂
long long qpow(long long a, long long b) {
    long long r = 1;
    while (b) {
        if (b & 1) r = r * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return r;
}

// 等比数列求和：1 + p + p^2 + ... + p^k  mod MOD
long long geo_sum(long long p, long long k) {
    if (k == 0) return 1;
    if (k % 2 == 1) // 奇数项：1 + p + ... + p^k = (1 + p^(k/2+1)) * (1 + p + ... + p^(k/2))
        return (1 + qpow(p, k / 2 + 1)) * geo_sum(p, k / 2) % MOD;
    else // 偶数项：1 + p + ... + p^k = p^(k/2) + (1 + p^(k/2+1)) * (1 + p + ... + p^(k/2-1))
        return (qpow(p, k / 2) + (1 + qpow(p, k / 2 + 1)) * geo_sum(p, k / 2 - 1)) % MOD;
}

int main() {
    long long a, b;
    scanf("%lld%lld", &a, &b);
    if (a == 0) { puts("0"); return 0; }
    long long ans = 1;
    // 分解质因数
    for (long long p = 2; p * p <= a; ++p) {
        if (a % p == 0) {
            long long cnt = 0;
            while (a % p == 0) { a /= p; ++cnt; }
            ans = ans * geo_sum(p % MOD, cnt * b) % MOD;
        }
    }
    if (a > 1) ans = ans * geo_sum(a % MOD, b) % MOD;
    printf("%lld\n", ans % MOD);
    return 0;
}
