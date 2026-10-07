/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-14 09:00
 * update_at: 2026-10-06 00:48
 */
#include <cstdio>

typedef long long ll;

const ll P = 10007; // 模数，是素数，Lucas 定理和费马小定理都依赖这一点
const int MAXP = 10007;

ll t, n, m;
ll f[MAXP]; // f[i] = i! mod P，只预处理 P 以内的阶乘

// 快速幂：a^b mod P
ll qpow(ll a, ll b) {
    ll res = 1;
    a %= P;
    while (b > 0) {
        if (b & 1) res = res * a % P;
        a = a * a % P;
        b >>= 1;
    }
    return res;
}

// 求 P 以内两个数的组合数 C(a, b) mod P，a、b 均小于 P
// 分母的逆元用费马小定理：x^(-1) = x^(P-2) mod P
ll small_comb(ll a, ll b) {
    if (b < 0 || b > a) return 0;
    return f[a] * qpow(f[b] * f[a - b] % P, P - 2) % P;
}

// Lucas 定理：把 C(n, m) mod P 按 P 进制拆成各位小组合数的乘积
// 若某一位 m 的数字大于 n 的数字，说明这一位上选不下，整个组合数为 0
ll lucas(ll n, ll m) {
    ll ans = 1;
    while (n > 0 || m > 0) {
        ans = ans * small_comb(n % P, m % P) % P;
        if (ans == 0) return 0; // 某位为 0，后面不用再算
        n /= P;
        m /= P;
    }
    return ans;
}

int main() {
    // 预处理阶乘表，所有询问共用
    f[0] = 1;
    for (int i = 1; i < P; i++) f[i] = f[i - 1] * i % P;

    scanf("%lld", &t);
    while (t--) {
        scanf("%lld %lld", &n, &m);
        printf("%lld\n", lucas(n, m));
    }
    return 0;
}
