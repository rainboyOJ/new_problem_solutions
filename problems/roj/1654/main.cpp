/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 00:41
 * update_at: 2026-10-06 00:41
 */

// L 形棋盘由两个左对齐矩形拼成：上矩形 b 行 a 列，下矩形 d 行 a+c 列（共享左侧 a 列）。
// 按上矩形里放几个车 i 分类：上矩形 C(b,i)*P(a,i)，下矩形的可用列被扣成 a+c-i，
// 贡献 C(d,k-i)*P(a+c-i,k-i)，对所有 i 求和即答案。

#include <cstdio>

typedef long long ll;

const ll MOD = 100003;          // 题面模数 10^5 + 3
const ll MAXN = 2005;           // a+c 最大 2000，所有组合/排列顶层下标都不超过它

ll n_max;                       // 表实际建到的最大行数
ll C[MAXN][MAXN];               // C[n][r] = 组合数 C(n, r) mod MOD，杨辉递推生成
ll P[MAXN][MAXN];               // P[n][r] = 下降幂 n(n-1)...(n-r+1) mod MOD，前缀积累乘

// 在 R 行 * Ccol 列的矩形里放 t 个互不攻击的车的方案数：
// 先选被占用的 t 行（C(R,t)），再给这 t 行依次配互不相同的列（P(Ccol,t)），两步独立。
// t 越界（不存在的方案）返回 0。
ll ways(ll R, ll Ccol, ll t) {
    if (t < 0 || t > R || t > Ccol)
        return 0;
    return C[R][t] * P[Ccol][t] % MOD;
}

void solve() {
    ll a, b, c, d, k;
    scanf("%lld %lld %lld %lld %lld", &a, &b, &c, &d, &k);

    // 组合/排列的顶层下标只会是 b、a+c、d、k，取最大者建表
    n_max = b;
    if (a + c > n_max) n_max = a + c;
    if (d > n_max) n_max = d;
    if (k > n_max) n_max = k;

    // 杨辉递推建组合数表：C(n,0)=1，C(n,r)=C(n-1,r-1)+C(n-1,r)
    for (ll n = 0; n <= n_max; ++n) {
        C[n][0] = 1;
        for (ll r = 1; r <= n; ++r)
            C[n][r] = (C[n - 1][r - 1] + C[n - 1][r]) % MOD;
    }

    // 前缀积建下降幂表：P[n][0]=1，P[n][r]=P[n][r-1]*(n-r+1)
    for (ll n = 0; n <= n_max; ++n) {
        P[n][0] = 1;
        for (ll r = 1; r <= n; ++r)
            P[n][r] = P[n][r - 1] * (n - r + 1) % MOD;
    }

    // 枚举上矩形（b 行 a 列）里的车数 i。
    // 上矩形占用的 i 列都在它的列集 {0..a-1} 内，而这个列集是下矩形列集的子集，
    // 所以下矩形恰好剩 a+c-i 列可用；上下两块行集不相交，行方向没有别的耦合。
    ll ans = 0;
    ll i_max = a;
    if (b < i_max) i_max = b;
    if (k < i_max) i_max = k;
    for (ll i = 0; i <= i_max; ++i) {
        ll up = ways(b, a, i);              // 上矩形方案数
        ll down = ways(d, a + c - i, k - i); // 下矩形可用列只剩 a+c-i
        ans = (ans + up * down) % MOD;
    }

    printf("%lld\n", ans);
}

int main() {
    solve();
    return 0;
}
