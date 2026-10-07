/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 01:19
 * update_at: 2026-10-06 01:19
 */

#include <cstdio>

typedef long long ll;

const ll MOD = 100003; // 题面要求的模数

ll m, n; // m 种宗教，n 个房间

// 计算 a^b mod MOD，快速幂
ll qpow(ll a, ll b) {
    ll res = 1;
    a %= MOD;
    while (b > 0) {
        if (b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

int main() {
    scanf("%lld %lld", &m, &n);

    // 全部状态数 m^n 减去不越狱数 m*(m-1)^(n-1)
    // n=1 时没有相邻对，m-1 的 0 次方为 1，公式给出 0，天然正确
    ll all_states = qpow(m, n);
    ll safe_states = m % MOD * qpow(m - 1, n - 1) % MOD;

    // 减法可能出负数，补回模数
    ll ans = ((all_states - safe_states) % MOD + MOD) % MOD;
    printf("%lld\n", ans);
    return 0;
}
