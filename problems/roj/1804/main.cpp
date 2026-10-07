/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-08 04:13
 * update_at: 2026-10-08 04:13
 */
// 一本通 1804《最大真因数》
// 合数 n 的最大真因数 = n / spf(n)（spf 为最小质因子），因为拿掉最小质因子后剩下的商最大。
// 于是答案 = F(r) - F(l-1)，其中 F(N) = Σ_{合数 c<=N} c / spf(c)。
// min_25 筛取权值 f(x)=x 求 F：把合数按最小质因子 p_j 分组，第 j 组是 n = p_j*m
// （m ∈ [p_j, N/p_j] 且 spf(m) >= p_j），每组贡献恰是 Σm，正是筛过程中被 p_j 划去的那些数除以 p_j 的和。
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef __int128 lll;

const int MAXS = 100005; // sqrt(5*10^9) ≈ 70710，留足余量

bool vis[MAXS];  // 线性筛的合数标记
ll prime[MAXS];  // prime[1..tot]：不超过 sqrt(N) 的质数，升序
lll sp[MAXS];    // sp[j] = 前 j 个质数之和（即「小于 p_{j+1} 的质数和」）
lll g1[MAXS];    // 大状态：下标 i=1..L，状态值 val = n/i > sqrt(n)
lll g2[MAXS];    // 小状态：下标就是状态值 x <= sqrt(n)
int tot;         // 质数个数

// 精确求 floor(sqrt(n))：先浮点开方再整数修正（n <= 5*10^9）
ll isqrt_ll(ll n) {
    ll x = sqrtl((long double)n);
    while (x > 0 && x * x > n) --x;
    while ((x + 1) * (x + 1) <= n) ++x;
    return x;
}

// 线性筛出 [2, lim] 的质数，并递推前缀和 sp
void build_prime(ll lim) {
    tot = 0;
    for (ll i = 0; i <= lim; i++) vis[i] = false;
    for (ll i = 2; i <= lim; i++) {
        if (!vis[i]) {
            prime[++tot] = i;
            sp[tot] = sp[tot - 1] + i;
        }
        for (int j = 1; j <= tot && i * prime[j] <= lim; j++) {
            vis[i * prime[j]] = true;
            if (i % prime[j] == 0) break;
        }
    }
}

// g[i] 的含义：状态值 w 下「质数 或 最小质因子 > 已筛质数」的所有数值和。
// 初始（一个质数都没筛）就是 2..w 的数值和 w(w+1)/2 - 1。
// 筛 p 时被划去的数是 p*m（m >= p 且 spf(m) >= p），其和 = p*(g(w/p) - sp[小于p的质数和])。
// 状态只有 floor(N/i) 这 2*sqrt(N) 个：值 > S 的按 n/i 存进 g1，值 <= S 的直接用值当下标存 g2。

// F(n) = Σ_{合数 c<=n} c / spf(c)
lll F(ll n) {
    if (n < 4) return 0;          // 1、2、3 都不是合数
    ll S = isqrt_ll(n);
    build_prime(S);
    ll L = n / (S + 1);           // 大状态个数：状态值 n/i > S 的 i 恰好是 1..L
    for (ll i = 1; i <= L; i++) {
        lll v = n / i;
        g1[i] = v * (v + 1) / 2 - 1;
    }
    for (ll x = 1; x <= S; x++) {
        lll v = x;
        g2[x] = v * (v + 1) / 2 - 1;
    }
    lll ans = 0;
    for (int j = 1; j <= tot; j++) {
        ll p = prime[j], p2 = p * p;
        lll pre = sp[j - 1];          // 小于 p 的质数之和
        ll hb = min(L, n / p2);       // 大状态里值 >= p^2 的个数，更小的状态无 p 的倍数可划
        for (ll i = 1; i <= hb; i++) {
            ll id = i * p;            // 状态值 n/i 再除以 p，即 floor(n/(i*p))
            lll cur = (id <= L) ? g1[id] : g2[n / id];
            lll d = cur - pre;
            if (i == 1) ans += d;     // i==1 是状态 n：最小质因子恰为 p 的合数贡献 Σm
            g1[i] -= d * p;
        }
        // 小状态倒序处理，保证读到的 g2[x/p] 还是上一阶段的值（x/p < x 未被本轮更新）
        for (ll x = S; x >= p2; x--) g2[x] -= (g2[x / p] - pre) * p;
    }
    return ans;
}

// 输出 128 位整数：逐位取余打印
void print_lll(lll x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    if (x > 9) print_lll(x / 10);
    putchar('0' + (int)(x % 10)); // 取值必在 0..9，转成 int 才能参与字符运算
}

int main() {
    ll l, r;
    if (scanf("%lld %lld", &l, &r) != 2) return 0;
    print_lll(F(r) - F(l - 1));
    putchar('\n');
    return 0;
}
