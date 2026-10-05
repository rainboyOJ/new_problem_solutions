/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 01:04
 * update_at: 2026-10-06 01:04
 */

// 有趣的数列：答案为第 n 项卡特兰数 C_n = (2n)! / (n! * (n+1)!)。
// 模数 P 是任意整数（不保证是质数），不能求逆元，
// 所以对每个质数 p 用勒让德公式算出 C_n 中 p 的指数，再用快速幂模 P 连乘。

#include <cstdio>

typedef long long ll;

const int MAXN = 2000005; // 需要 2n 以内的数，n <= 1e6

int n;
ll P;

bool is_composite[MAXN]; // is_composite[i] = true 表示 i 是合数
int primes[MAXN / 10];   // 存 2n 以内的全部质数，约 2e6/ln(2e6) 个，够用
int prime_cnt = 0;

// 线性筛：筛出 2n 以内的全部质数
void sieve(ll limit) {
    for (ll i = 2; i <= limit; ++i) {
        if (!is_composite[i]) primes[prime_cnt++] = i;
        for (int j = 0; j < prime_cnt; ++j) {
            ll nxt = (ll)primes[j] * i;
            if (nxt > limit) break;
            is_composite[nxt] = true;
            if (i % primes[j] == 0) break; // primes[j] 是 i 的最小质因子，避免重复筛
        }
    }
}

// 勒让德公式：计算 x! 中质因子 p 的指数
ll legendre(ll x, ll p) {
    ll cnt = 0;
    while (x > 0) {
        cnt += x / p;
        x /= p;
    }
    return cnt;
}

// 快速幂：p^e mod P
ll qpow(ll p, ll e) {
    ll res = 1;
    ll base = p % P;
    while (e > 0) {
        if (e & 1) res = res * base % P;
        base = base * base % P;
        e >>= 1;
    }
    return res;
}

int main() {
    scanf("%d %lld", &n, &P);
    ll m = 2LL * n;
    sieve(m);
    ll ans = 1;
    // 对每个质数 p，C_n 中 p 的净指数 = E(2n) - E(n) - E(n+1)，必然非负
    for (int i = 0; i < prime_cnt; ++i) {
        ll p = primes[i];
        ll exp = legendre(m, p) - legendre(n, p) - legendre(n + 1, p);
        if (exp > 0) ans = ans * qpow(p, exp) % P;
    }
    printf("%lld\n", ans);
    return 0;
}
