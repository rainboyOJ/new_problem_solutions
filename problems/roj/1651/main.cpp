/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 00:35
 * update_at: 2026-10-06 00:35
 */
// 古代猪文：求 G^P mod 999911659，其中 P = Σ_{k | N} C(N, k)。
// 链路：费马小定理降幂 -> P mod (MOD-1)，MOD-1 = 2×3×4679×35617，
// 四个素因子下分别用 Lucas 定理求 P，最后用中国剩余定理合并出指数。
#include <cstdio>

typedef long long ll;

const ll MOD = 999911659;      // 题目模数，是质数
const int PCNT = 4;
const ll crt_p[PCNT] = {2, 3, 4679, 35617}; // MOD1 的全部素因子
const ll MAXP = 35617;         // 最大的素因子，决定阶乘表大小

// 预处理每个素因子 p 下的阶乘表 fact[i] = i! mod p 和逆元表 inv[i] = (i!)^{-1} mod p
ll fact[PCNT][MAXP];
ll inv[PCNT][MAXP];

ll qpow(ll base, ll e, ll mod) { // 快速幂：base^e mod mod
    ll ans = 1;
    base %= mod;
    while (e > 0) {
        if (e & 1) ans = ans * base % mod;
        base = base * base % mod;
        e >>= 1;
    }
    return ans;
}

// 一次性建出四个素因子共用的两张表，逆元表由末项倒推
void build_tables() {
    for (int i = 0; i < PCNT; ++i) {
        ll p = crt_p[i];
        fact[i][0] = 1;
        for (ll j = 1; j < p; ++j) fact[i][j] = fact[i][j - 1] * j % p;
        inv[i][p - 1] = qpow(fact[i][p - 1], p - 2, p); // p 是质数，逆元 = 幂 p-2
        for (ll j = p - 1; j >= 1; --j) inv[i][j - 1] = inv[i][j] * j % p;
    }
}

// C(n, k) mod p，p 为质数，逐位拆 p 进制（Lucas 定理）
// 某一位上 k_i > n_i 时整个乘积为 0，这正好覆盖了 p | C(n, k) 的情形
ll lucas(int id, ll n, ll k) {
    ll p = crt_p[id];
    ll ans = 1;
    while (n > 0 || k > 0) {
        ll ni = n % p, ki = k % p;
        if (ki > ni) return 0;      // 这一位选多了，组合数被 p 整除
        ans = ans * fact[id][ni] % p * inv[id][ki] % p * inv[id][ni - ki] % p;
        n /= p;
        k /= p;
    }
    return ans;
}

// 求 P mod p（p 是 MOD1 的一个素因子），N 的约数现场枚举、不落地保存
ll sum_crt(ll n, int id) {
    ll p = crt_p[id];
    ll sum = 0;
    for (ll d = 1; d * d <= n; ++d) {
        if (n % d != 0) continue;
        sum = (sum + lucas(id, n, d)) % p; // k 与 N/k 都遍历全部约数，各收一次
        if (d != n / d)                    // 完全平方数时中间那个约数只算一次
            sum = (sum + lucas(id, n, n / d)) % p;
    }
    return sum;
}

int main() {
    ll n, g;
    scanf("%lld %lld", &n, &g);

    if (g % MOD == 0) { // G 是模数的倍数，任何正次幂都是 0，且费马降幂失效
        printf("0\n");
        return 0;
    }

    build_tables();

    // CRT 逐项增量合并：r 是已合并部分的余数，M 是已合并部分的模数，
    // M 始终是若干不同素因子之积，与下一个 p 互素，逆元必然存在
    ll r = 0, M = 1;
    for (int i = 0; i < PCNT; ++i) {
        ll p = crt_p[i];
        ll residue = sum_crt(n, i);
        ll t = (residue - r) % p * qpow(M % p, p - 2, p) % p; // 令 r + t*M ≡ residue (mod p)
        if (t < 0) t += p;
        r = r + t * M; // 不取模也不会溢出：最终 r < 999911658，中间 t*M < 35617*MOD1
        M = M * p;
    }

    // 费马小定理：G^P ≡ G^(P mod (MOD-1)) (mod MOD)
    printf("%lld\n", qpow(g % MOD, r, MOD));
    return 0;
}
