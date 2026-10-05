/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 00:54
 * update_at: 2026-10-06 00:54
 */
#include <cstdio>

typedef long long ll;

const ll P = 1000003; // 模数，质数，Lucas 分解的进制

ll fact[1000003]; // fact[i] = i! mod P，供 Lucas 每一位查表

// 快速幂：求 base^exp mod P，用于费马小定理求逆元
ll power(ll base, ll exp) {
    ll res = 1;
    base %= P;
    while (exp > 0) {
        if (exp & 1) {
            res = res * base % P;
        }
        base = base * base % P;
        exp >>= 1;
    }
    return res;
}

// 组合数 C(n, k) mod P：n 可达 2e9 超过 P，按 Lucas 定理逐位相乘
ll comb(ll n, ll k) {
    ll res = 1;
    while (n > 0 || k > 0) {
        ll a = n % P; // 当前 P 进制位
        ll b = k % P;
        if (b > a) {
            return 0; // 某一位下标超过上标，整项为 0
        }
        res = res * fact[a] % P;
        res = res * power(fact[b], P - 2) % P;
        res = res * power(fact[a - b], P - 2) % P;
        n /= P;
        k /= P;
    }
    return res;
}

int main() {
    fact[0] = 1;
    for (ll i = 1; i < P; i++) {
        fact[i] = fact[i - 1] * i % P;
    }

    ll t;
    scanf("%lld", &t);
    while (t--) {
        ll n, l, r;
        scanf("%lld%lld%lld", &n, &l, &r);
        ll m = r - l + 1; // 元素取值个数
        // 逐长度求和由 hockey-stick 恒等式折叠为 C(m+n, n)，
        // 该式包含了长度为 0 的空序列，题目要求长度至少为 1，故减 1
        ll ans = (comb(m + n, n) - 1 + P) % P;
        printf("%lld\n", ans);
    }
    return 0;
}
